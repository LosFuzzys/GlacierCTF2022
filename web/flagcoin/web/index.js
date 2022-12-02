const express = require("express");
const mongoose = require("mongoose");
const { loginCheck } = require("./src/auth.js");

const app = express();

const PORT = process.env.PORT || 8080;
const COOKIE_SECRET = process.env.COOKIE_SECRET || 'CHANGE_ME';

app.use(require("cookie-parser")(COOKIE_SECRET));
app.use('/panel', loginCheck);
app.use(express.static("public"));
app.use("/graphql", require("./src/graphql.js"));
app.use('/panel', express.static('private/panel.html'))
app.use('/panel.js', express.static('private/panel.js'))
app.use('/style.css', express.static('public/style.css'))

mongoose.connect(process.env.DB_URL);

app.listen(PORT, () => console.log(`web/payment-pal listening on port ${PORT}`));
