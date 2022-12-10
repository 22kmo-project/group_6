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
            'insert into tunnus (id_asiakas,id_card,lukitus,card_pin) values(?,?,?,?)',
            [add_data.id_asiakas,add_data.id_card,add_data.lukitus, hashedPin],
            callback);
        });
    },
    delete: function (id, callback) {
        return db.query('delete from tunnus where id_card=?', [id], callback);
    },
    update: function (id, update_data, callback) {
        bcrypt.hash(update_data.card_pin, saltRounds, function(err, hashedPin) {
        return db.query(
            'update tunnus set id_asiakas=?, id_card=?, lukitus=?, card_pin=? where id_card=?',
            [update_data.id_asiakas, update_data.id_card, update_data.lukitus, hashedPin, id],
            callback);
        });
    },
    checkPassword: function(id_card,callback){
        return db.query('select card_pin from tunnus where id_card=? and lukitus<3',[id_card],callback);   
    },
    /*tunnusLukitusLaskuri: function(id,callback){
        return db.query('update tunnus set lukitus+1 where id_card=?',[id],callback);   
    },*/
    tunnusLukitus: function(id,callback){
        return db.query('update tunnus set lukitus=lukitus+1 where id_card=?',[id],callback);   
    },
    tunnusAvaus: function(id,callback){
        return db.query('update tunnus set lukitus=0 where id_card=?',[id],callback);   
    },
    getUserName: function(id,callback){
        return db.query('select fname from asiakas inner join tunnus on asiakas.id_asiakas=tunnus.id_asiakas where tunnus.id_card=?',[id],callback);
    }
};

module.exports = tunnus;