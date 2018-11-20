#include "../core/stsclasses.h" 
/*
the interpreter parses the file and calls functions in other files
*/

std::vector<string> sts::parse(std::vector<string> prg){ 
    std::vector<string> x;
    int y = 0;
    while (y!=prg.size()){
        int z = 0;
        bool inquotes = false;
        x.resize(x.size()+1);
        
        while (prg[y][0]==' ')
            prg[y].erase(prg[y].begin());
        
        bool endscope = (prg[y]=="}\0");

        while (z!=prg[y].size()){
            if (prg[y][z]=='"'){
                if (inquotes == false){
                    inquotes = true;
                }
                else{
                    inquotes = false;
                }
            }
            // this is what checks for chars to remove from prs version
            if (((prg[y][z]==' ') || (prg[y][z]==',') || (prg[y][z]=='\n') || (prg[y][z]=='(') || (prg[y][z]==')') || (prg[y][z]=='.')) && (inquotes==false)){
                x.resize(x.size()+1);
                z++;
                continue;
            }
            else if  ((prg[y][z]==';') && (inquotes==false)) {
                x.push_back( string(1,prg[y][z]) );
                break;
            }
            else if ((((prg[y][z]=='@') || (prg[y][z]=='[') || (prg[y][z]==']')) && (inquotes==false)) || ((prg[y][z]=='}') && (endscope==true))) {
                x.push_back( string(1,prg[y][z]) );
                x.resize(x.size()+1);
            }
            else if ((prg[y][z]=='{') || (prg[y][z]=='}') || (prg[y][z]=='\t') && (inquotes==false)) {
                z++;
                continue;
            }
            else
                x[x.size()-1]+=prg[y][z];

            z++;
        }
        y++;
    }
    if (!term)
        x.back().pop_back(); //removes EOF char from end of file so it can parse

    for (int i = 0; i<x.size(); i++) {
        if ((x[i]=="\0") || (x[i]==""))
            x.erase(x.begin() + i);
    }
    return x;
}