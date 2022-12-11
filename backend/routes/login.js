const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const tunnus = require('../models/tunnus_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.id_card && request.body.card_pin){
      const id_card = request.body.id_card;
      const card_pin = request.body.card_pin;
      console.log(id_card);
      console.log(card_pin);
        tunnus.checkPassword(id_card, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError.errno);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(card_pin,dbResult[0].card_pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ username: id_card });
                  response.send(token);
                }
                else {
                    console.log("wrong card_pin");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("id_card or card_pin missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
    dotenv.config();
    return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports = router;