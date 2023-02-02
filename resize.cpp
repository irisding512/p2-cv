// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Matrix.h"
#include <string>
#include <cstring>

#include "Image.h"
#include "processing.h"

using namespace std;

int main(int argc,char *argv[]) {
   
    ifstream fin;
    ofstream fout;
    string filename = argv[1], outputfile = argv[2];

    if((argc != 4) && (argc !=5)){ 
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]" << endl; 
        cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;

          return 1;
    }
  
    Image *img = new Image;

    fin.open(filename);
    fout.open(outputfile);

    if(!fin.is_open()){ 
        cout << "Error opening file: " << filename << endl;
        
          return 1;
    }

    if(!fout.is_open()){ 
        cout << "Error opening file: " << outputfile << endl;
        
          return 1;
    }

    Image_init(img, fin);
    const Image *imgptr = img;

    if(argc == 5){ 
        if(Image_height(imgptr) < atoi(argv[4]) || atoi(argv[4]) <= 0 || 
           Image_width(imgptr) < atoi(argv[3]) || atoi(argv[3]) <= 0){
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]" << endl;
            cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            
              return 1;
        }
    }
    else { 
        if(Image_width(imgptr) < atoi(argv[3]) || atoi(argv[3]) <= 0){
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]" << endl;
            cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            
              return 1;
        }
    }

    if(argc == 4){
        seam_carve_width(img, atoi(argv[3]));
        Image_print(imgptr, fout);

          delete img;
          return 0;
    }

    seam_carve(img, atoi(argv[3]), atoi(argv[4]));
    Image_print(imgptr, fout);

      delete img;
      return 0;

}
