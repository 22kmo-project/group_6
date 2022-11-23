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
                'insert into tilioikeus (id_tilioikeus,id_tili,id_user) values(?,?,?)',
                [add_data.id_tilioikeus, add_data.id_tili, add_data.id_user],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from tilioikeus where id_tilioikeus=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update tilioikeus set id_tilioikeus=?,id_tili=?, id_user=?',
                [update_data.id_tilioikeus, update_data.id_tili, update_data.id_user, id],
                callback);
   
    },
   
   
  
};
module.exports = tilioikeus;