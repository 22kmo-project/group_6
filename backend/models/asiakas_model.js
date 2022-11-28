const db = require('../database');


const saltRounds = 10;

const asiakas = {
    getById: function (id, callback) {
        return db.query('select * from asiakas where id_user=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from asiakas', callback);
    },
    add: function (add_data, callback) {
       
            return db.query(
                'insert into asiakas (id_user,fname,lname,address,phoneNumber) values(?,?,?,?,?)',
                [add_data.id_user, add_data.fname, add_data.lname, add_data.address, add_data.phoneNumber],
                callback);
    },
   
    delete: function (id, callback) {
        return db.query('delete from asiakas where id_user=?', [id], callback);
    },
    update: function (id, update_data, callback) {
       
            return db.query(
                'update asiakas set fname=?,lname=?, address=?, phoneNumber=?  where id_user=?',
                [update_data.fname, update_data.lname, update_data.address, update_data.phoneNumber, id],
                callback);
   
    },
    getAllInfo: function(callback){
        return db.query('select fname, lname, address, phoneNumber from asiakas',callback);
    },
    getUserInfo: function(id,callback){
        return db.query('select fname, lname, address, phoneNumber from asiakas inner join tunnus on tunnus.id_card=asiakas.id_card where tunnus.id_card=?',[id],callback);
    }
  
};
module.exports = asiakas;