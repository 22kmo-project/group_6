var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var tiliRouter = require('./routes/tili');
var tunnusRouter = require('./routes/tunnus');
var asiakasRouter = require('./routes/asiakas');
var kortinoikeusRouter = require('./routes/kortinoikeus');
var tilioikeusRouter = require('./routes/tilioikeus');
var tilitapahtumaRouter = require('./routes/tilitapahtuma');
var loginRouter = require('./routes/login');
var asiakastiedotRouter = require('./routes/asiakastiedot');
var tilitiedotRouter = require('./routes/tilitiedot');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/login', loginRouter);

//app.use(authenticateToken);

app.use('/users', usersRouter);
app.use('/tili', tiliRouter);
app.use('/tunnus', tunnusRouter);
app.use('/asiakas', asiakasRouter);
app.use('/kortinoikeus', kortinoikeusRouter);
app.use('/tilioikeus', tilioikeusRouter);
app.use('/tilitapahtuma', tilitapahtumaRouter);
app.use('/asiakastiedot', asiakastiedotRouter);
app.use('/tilitiedot', tilitiedotRouter);


function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

module.exports = app;
