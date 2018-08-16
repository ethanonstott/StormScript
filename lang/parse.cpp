#include "stsclasses.h" 
/*
the compiler parses the file and calls functions in other files
*/

std::vector<string> sts::parse(std::vector<string> prg){
    std::vector<string> x;
    int y = 0;
    while (y!=prg.size()){
        int z = 0;
        x.resize(x.size()+1);
        bool inquotes = false;
        while (z!=prg[y].size()){
            if (prg[y][z]=='"'){
                if (inquotes == false){
                    inquotes = true;
                }
                else{
                    inquotes = false;
                }
            }
            // this is what checks for chars to remove from parsed version
            if (((prg[y][z]==' ') || (prg[y][z]=='\n') || (prg[y][z]=='(') || (prg[y][z]==')')) && (inquotes==false)){
                x.resize(x.size()+1);
                z++;
                continue;
            }
            else if (prg[y][z]=='\t'){
                z++;
                continue;
            }
            else{
                x[x.size()-1]+=prg[y][z];
            }
            z++;
        }

        y++;
    }
    x[x.size()-1].pop_back(); //removes EOF char from end of file so I can parse
    return x;
}

void sts::interp(string fname, std::vector<string> prg, int psize){
    prs = parse(prg);
    for (int x = 0; x<=prs.size()-1; x++){
        if (prs[x]=="do{"){
            std::vector<stsvars> vars;
            int y = x+1;
            int times;
            int endreq = 1;
            while (true){
                if (prs[y]=="out"){
                    out(y,vars);
                }
                else if (prs[y]=="in"){
                    vars.resize(vars.size()+1);
                    vars[vars.size()-1]=in(y);
                    y+=2;
                }
                else if (prs[y]=="if"){
                    if (compare(y,vars)){
                        endreq+=1;
                    }
                    else{
                        while (prs[y]!="}end;"){
                            y++;
                        }
                    }
                }
                else if (prs[y]=="int"){
                    vars.resize(vars.size()+1);
                    vars[vars.size()-1]=declare('i',y);
                }
                else if (prs[y]=="str"){
                    vars.resize(vars.size()+1);
                    vars[vars.size()-1]=declare('s',y);
                }
                else if (prs[y]=="}end;"){
                    endreq-=1;
                    if (endreq==0){
                        break;
                    }
                }
                y++;
            }
        }
    }
}   