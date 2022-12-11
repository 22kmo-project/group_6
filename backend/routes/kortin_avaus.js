const express = require('express');
const router = express.Router();
const tunnus = require('../models/tunnus_model');


router.put('/:id', 
function(request, response) {
  tunnus.tunnusAvaus(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;