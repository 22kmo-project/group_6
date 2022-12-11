const express = require('express');
const router = express.Router();
const asiakas = require('../models/tunnus_model');


router.get('/:id',function(request,response){
    const id=request.params.id;
    asiakas.getUserName(id,function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});


module.exports=router;