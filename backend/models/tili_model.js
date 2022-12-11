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
                'insert into tili (id_tili,account_balance) values(?,?)',
                [add_data.id_tili, add_data.account_balance],
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
    getAllAccounts: function(callback){
        return db.query('select id_tili, account_balance from tili',callback);
    },
    getUserAccounts: function(id,callback){
        return db.query('select tili.id_tili, account_balance from tili inner join kortinoikeus on tili.id_tili=kortinoikeus.id_tili inner join tunnus on kortinoikeus.id_card=tunnus.id_card where kortinoikeus.id_card=?',[id],callback);
    }
  
};
module.exports = tili;