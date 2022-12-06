const db = require('../database');
const bcrypt = require('bcryptjs');
const saltRounds = 10;


const tunnus = {
    getById: function (id, callback) {
        return db.query('select * from tunnus where id_card=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from tunnus', callback);
    },
    add: function (add_data, callback) {
        bcrypt.hash(add_data.card_pin, saltRounds, function(err, hashedPin) {
        return db.query(
            'insert into tunnus (id_asiakas,id_card,card_pin) values(?,?,?)',
            [add_data.id_asiakas,add_data.id_card, hashedPin],
            callback);
        });
    },
    delete: function (id, callback) {
        return db.query('delete from tunnus where id_card=?', [id], callback);
    },
    update: function (id, update_data, callback) {
        bcrypt.hash(update_data.id_asiakas, update_data.card_pin, saltRounds, function(err, hashedPin) {
        return db.query(
            'update tunnus set id_asiakas=?, id_card=?, card_pin=? where id_card=?',
            [update_data.id_asiakas,update_data.id_card,  hashedPin, id],
            callback);
        });
    },
    checkPassword: function(id_card,callback){
        return db.query('select card_pin from tunnus where id_card=?',[id_card],callback);
    }
};

module.exports = tunnus;