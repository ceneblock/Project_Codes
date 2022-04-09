// define a function to capture images using the RaspiCam library

int get_image(){
	//open camera object
    raspicam::RaspiCam Camera; 
    if ( !Camera.open()) {cerr<<"Error opening camera"<<endl;return -1;}
    sleep(3);

    //capture
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    //get camera image 
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );
    
    //save
    std::ofstream outFile ( "image.ppm",std::ios::binary );
    outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    cout<<"Image saved at image.ppm"<<endl;   
    delete data;
    
    return 0;
}
