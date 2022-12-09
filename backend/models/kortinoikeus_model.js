const db = require('../database');


const saltRounds = 10;

const kortinoikeus = {
    getById: function (id, callback) {
        return db.query('select * from kortinoikeus where id_oikeus=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from kortinoikeus', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into kortinoikeus (id_oikeus,id_tili,id_card) values(?,?,?)',
                [add_data.id_oikeus, add_data.id_tili, add_data.id_card],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from kortinoikeus where id_oikeus=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update kortinoikeus set id_tili=?, id_card=? where id_oikeus=?',
                [update_data.id_tili, update_data.id_card, id],
                callback);
   
    },
   
   
  
};
module.exports = kortinoikeus;