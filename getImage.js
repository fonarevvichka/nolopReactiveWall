const NodeWebcam = require( "node-webcam" );

var opts = {
    width: 1280,
    height: 720,
    quality: 100,
    delay: 0,
 
 
    //Save shots in memory
 
    saveShots: true,
 
 
    // [jpeg, png] support varies
    // Webcam.OutputTypes
 
    output: "jpeg",
 
    device: false,
 
    callbackReturn: "location",
 
    verbose: false
 
};

var Webcam = NodeWebcam.create( opts );

Webcam.capture( "test_picture", function( err, data ) {
    Webcam.getBase64(0, function(err, data){
        console.log(data)
    });
} );
