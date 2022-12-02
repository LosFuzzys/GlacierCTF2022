const crypto = require("crypto");

const db = require("./db.js");

const getUser = (req) => {
  const username = req.signedCookies.session;
  if(!username) {
    throw new Error("You are not logged in");
  }
  return db.User.findOne({ username: username }).lean().exec();
};

const setUser = (res, username) => {
  res.cookie("session", username, {signed: true});
};

const loginCheck = (req, res, next) => {
  if (req.signedCookies.session) {
      next();
  } else {
      var err = new Error('Not authorized! Go back!');
      err.status = 401;
      return next(err);
  }
}

module.exports = { getUser, setUser, loginCheck };