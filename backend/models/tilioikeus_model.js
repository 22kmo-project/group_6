const db = require('../database');


const saltRounds = 10;

const tilioikeus = {
    getById: function (id, callback) {
        return db.query('select * from tilioikeus where id_tilioikeus=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from tilioikeus', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into tilioikeus (id_tilioikeus,id_tili,id_asiakas) values(?,?,?)',
                [add_data.id_tilioikeus, add_data.id_tili, add_data.id_asiakas],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from tilioikeus where id_tilioikeus=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update tilioikeus set id_tili=?, id_asiakas=? where id_tilioikeus=?',
                [update_data.id_tili, update_data.id_asiakas, id],
                callback);
   
    },
   
   
  
};
module.exports = tilioikeus;