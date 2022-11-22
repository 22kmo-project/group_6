const db = require('../database');


const saltRounds = 10;

const tili = {
    getById: function (id, callback) {
        return db.query('select * from tili where id_tili=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from tili', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into tili (id_tili,account_balance,id_card) values(?,?,?)',
                [add_data.id_tili, add_data.account_balance, add_data.id_card],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from tili where id_tili=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update tili set id_tili=?,account_balance=?',
                [update_data.id_tili, update_data.account_balance, id],
                callback);
   
    },
   
   
  
};
module.exports = tili;