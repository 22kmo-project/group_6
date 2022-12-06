const express = require('express');
const router = express.Router();
const asiakas = require('../models/asiakas_model');

router.get('/',function(request,response){
    asiakas.getAllInfo(function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});
router.get('/:id',function(request,response){
    const id=request.params.id;
    asiakas.getUserInfo(id,function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});


module.exports=router;