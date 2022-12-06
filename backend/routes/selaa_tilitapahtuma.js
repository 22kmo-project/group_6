const express = require('express');
const router = express.Router();
const tilitapahtuma = require('../models/tilitapahtuma_model');

router.get('/:id', function(request,response){
    const id=request.params.id;
    tilitapahtuma.getByIdCard(id,function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
});

module.exports=router;