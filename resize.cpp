//Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include "processing.h" 
#include <fstream>
#include "Matrix.h"
#include "Image.h"
#include <iostream>
#include <string>

using namespace std;
  
int main(int argc, char *argv[]) {
    string filename = argv[1];
    string output_file = argv[2]; 
    int desiredWidth, desiredHeight = 0;

    Image *img = new Image;
    ifstream fin; 
    ofstream fout;

    fin.open(filename); 
    fout.open(output_file);
    
    if (!fin.is_open()){
        cout << "Error opening file: " << filename << endl;
          delete img;
          return -1;
    }

    if (!fout.is_open()){
        cout << "Error opening file: " << output_file << endl;
          delete img;
          return -1;
    }

    Image_init(img,fin);

    if(argc == 5){
        desiredWidth = atoi(argv[3]), desiredHeight = atoi(argv[4]);
        if(!(desiredWidth > 0 && desiredWidth <= Image_width(img)) || 
          !(desiredHeight > 0 && desiredHeight <= Image_height(img))){
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]" << endl;
            cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
              delete img;
              return -1;
        }
    }

    else if(argc == 4){
        desiredWidth = atoi(argv[3]), desiredHeight = Image_height(img);
        if(!(desiredWidth > 0 && desiredWidth <= Image_width(img)) || 
        !(desiredHeight > 0 && desiredHeight <= Image_height(img))){
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]" << endl;
            cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
              delete img;
              return -1;
        }
    }

    else{
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]" << endl;
        cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
          delete img;
          return -1;
    }

    seam_carve(img,desiredWidth,desiredHeight);
    Image_print(img,fout);
    fout.close(), fin.close();

      delete img;
      return 0;
} 
