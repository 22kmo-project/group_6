const mysql = require('mysql');
const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'banksimul',
  password: 'netpass',
  database: 'banksimul'
});
module.exports = connection;