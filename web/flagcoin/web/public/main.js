const $ = document.querySelector.bind(document);

const graphql = async (query, variables) => {
  let res = await fetch("/graphql", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ query, variables })
  });
  return await res.json();
};

const login = async () => {
  let username = $("input[name=user]").value;
  let password = $("input[name=pass]").value;
  let res = await graphql(`
      mutation($username: String!, $password: String!) { 
        login(username: $username, password: $password) { 
          username 
        } 
      }
      `, {
    username,
    password
  });

  if (res.errors) {
    alert('login error ' + res.errors[0].message);
  } else {
    location.href = '/panel';
  }
};
