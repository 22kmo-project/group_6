const db = require('../database');


const saltRounds = 10;

const tilitapahtuma = {
    getById: function (id, callback) {
        return db.query('select * from tilitapahtuma where id_tapahtuma=?', [id], callback);
    },

    getAll: function (callback) {
        return db.query('select * from tilitapahtuma', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into tilitapahtuma (id_tapahtuma,id_tili,date,transaction,amount,id_card) values(?,?,?,?,?,?)',
                [add_data.id_tapahtuma, add_data.id_tili, add_data.date, add_data.transaction, add_data.amount, add_data.id_card],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from tilitapahtuma where id_tapahtuma=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update tilitapahtuma set id_tili=?,date=?,transaction=?,amount=?,id_card=? where id_tapahtuma=?',
                [update_data.id_tili, update_data.date, update_data.transaction, update_data.amount, update_data.id_card, id],
                callback);
   
    },
    getByIdCard: function (id, callback) {
        return db.query('select * from tilitapahtuma where tilitapahtuma.id_card=?', [id], callback);
    },
   
  
};
module.exports = tilitapahtuma;