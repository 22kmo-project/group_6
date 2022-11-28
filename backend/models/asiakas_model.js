const db = require('../database');


const saltRounds = 10;

const asiakas = {
    getById: function (id, callback) {
        return db.query('select * from asiakas where id_asiakas=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from asiakas', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into asiakas (id_asiakas,fname,lname,address,phoneNumber) values(?,?,?,?,?)',
                [add_data.id_asiakas, add_data.fname, add_data.lname, add_data.address, add_data.phoneNumber],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from asiakas where id_asiakas=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update asiakas set fname=?,lname=?, address=?, phoneNumber=?  where id_asiakas=?',
                [update_data.fname, update_data.lname, update_data.address, update_data.phoneNumber, id],
                callback);
   
    },
   
   
  
};
module.exports = asiakas;