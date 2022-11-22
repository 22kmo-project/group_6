const db = require('../database');


const saltRounds = 10;

const tunnus = {
    getById: function (id, callback) {
        return db.query('select * from tunnus where id_card=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from tunnus', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into tunnus (id_card,card_pin) values(?,?)',
                [add_data.id_card, add_data.card_pin],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from tunnus where id_card=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update tunnus set id_card=?,card_pin=?',
                [update_data.id_card, update_data.card_pin, id],
                callback);
   
    },
   
   
  
};
module.exports = tunnus;