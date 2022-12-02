const { graphqlHTTP } = require('express-graphql');
const { GraphQLObjectType, GraphQLString, GraphQLInt, GraphQLSchema } = require('graphql');
const { GraphQLJSON } = require('graphql-type-json');

const db = require("./db.js");
const auth = require("./auth.js");

const userType = new GraphQLObjectType({
  name: 'User',
  fields: {
    username: { type: GraphQLString },
    password: { type: GraphQLString },
    coins: { type: GraphQLInt },
  }
});

const voucherType = new GraphQLObjectType({
  name: 'Voucher',
  fields: {
    code: { type: GraphQLString },
    message: { type: GraphQLString },
    coins: { type: GraphQLInt },
  }
});

const queryType = new GraphQLObjectType({
  name: 'Query',
  fields: {
    info: {
      type: userType,
      args: {},
      resolve: (_, args, context, __) => { return info(args, context) }
    }
  }
});

const mutationType = new GraphQLObjectType({
  name: 'Mutation',
  fields: {
    login: {
      type: userType,
      args: {
        username: { type: GraphQLString },
        password: { type: GraphQLString },
      },
      resolve: (_, args, context, __) => { return login(args, context) }
    },
    register_beta_user: {
      type: userType,
      args: {
        username: { type: GraphQLString },
        password: { type: GraphQLString },
      },
      resolve: (_, args, context, __) => { return register(args, context) }
    },
    redeem: {
      type: voucherType,
      args: {
        voucher: { type: GraphQLJSON },
      },
      resolve: (_, args, context, __) => { return redeem(args, context) }
    }
  }
});

const schema = new GraphQLSchema({query: queryType, mutation: mutationType});

const info = (_, { req }) => {
  return { ...auth.getUser(req), password: null };
};

const login = ({ username, password }, { res }, context) => {
  return db.User.findOne({ username: username }).lean().exec()
    .then(user => {
      if(!user) {
        throw new Error("User does not exist");
      }
      if(user.password !== password) {
        throw new Error("Wrong password");
      }
      
      auth.setUser(res, username);
      return { ...user, password: null };
    })
    .catch(e => {
      throw new Error("Error occured "+e);
    });
};

const register = ({ username, password }, { res }, context) => {
  const userJSON = {
    username: username,
    password: password,
    coins: 0
  }
  const user = new db.User(userJSON);
  return user.save()
    .then(r => {
      auth.setUser(res, username);
      return { ...userJSON, password: null };
    })
    .catch(e => {
      throw new Error("could not create user: "+e);
    });
};

const redeem = ({ voucher }, { req }) => {
  return auth.getUser(req)
    .then(user => {
      if(!user) {
        throw new Error("You must be logged in");
      }
      return db.Voucher.findOne({ code: voucher.code }).lean().exec()
        .then(dbvoucher => {
          if(!dbvoucher) {
            throw new Error("Voucher does not exist");
          }
          user.coins += dbvoucher.coins;
          // "TODO" delete voucher
          return dbvoucher;
        })
  })
  .catch(e => {
    throw new Error("Error occured "+e);
  });
};

module.exports = graphqlHTTP(async (req, res) => ({
  schema: schema,
  graphiql: false,
  context: { req, res }
}));
