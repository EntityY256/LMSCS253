#include <bits/stdc++.h>
#include <chrono>
// using namespace std;

std::vector<std::vector<std::string>> content,content2;
std::vector<std::string> toupdate;

void readfile(std::string fname) { 
    std::vector<std::string> row;
    std::string line, word;

    std::fstream file(fname, std::ios::in);
    if (file.is_open()) {
        if (file.peek() == std::ifstream::traits_type::eof() && fname !="issued_books_data.csv" && fname !="borrow_history.csv") { // Check if file is empty
            std::cout << "The file " << fname << " is empty.\n";
            return; // Exit function early, but don't crash
        }

        while (std::getline(file, line)) {
            row.clear();
            std::stringstream str(line);
            while (std::getline(str, word, ',')) row.push_back(word);
            content.push_back(row);
        }
    } else {
        std::cout << "Could not open the file " << fname << "\n";
    }
}
void writefile(std::vector<std::vector<std::string>> par, std::string fname) {  
    std::fstream fout(fname, std::ios::out);  
    if (!fout) {  
        std::cerr << "Error opening file for writing: " << fname << std::endl;
        return;
    }

    for (auto &x : par) {  
        for (size_t i = 0; i < x.size(); ++i) {  
            fout << x[i];  
            if (i < x.size() - 1) fout << ",";  
        }
        fout << "\n";  
    }
    fout.close();
}
void writefileappend(std::vector<std::string> par, std::string fname){  
    std::fstream fout(fname,std::ios::out | std::ios::app);
    for(auto x:par){
        fout<<x;
        if(x!=par.back()) fout<<",";
    }
    fout<<"\n";
}
void printdata(std::vector<std::vector<std::string>> par){
    int c=1;
    for(auto x:par){
        std::cout<<c<<". ";
        for(auto y:x){
            std::cout<<y;
            if(y!=x.back()) std::cout<<" | ";
        }
        c++;
        std::cout<<"\n";
    }
}
void printdata_notpassword(std::vector<std::vector<std::string>> par){
    int c=1;
    for(auto x:par){
        std::cout<<c<<". ";
        std::cout<<x[0]<<" | "<<x[1]<<" | "<<x[3]<<'\n';
        c++;
    }
}

class User{
    private:
    std::string password;
    public:
    std::string name;
    std::string id;
    std::vector<std::string> isbns_issued;
        
        void see_history(std::string id);
        void reserve_book(std::string id, std::string bookname);
        void unreserve_book(std::string id,std::string bookname);
        void reserve_to_issue(std::string id,std::string type_user);
        void see_all_books(std::string id);
        void see_issued_books(std::string id);
        void logout();
        void issue_book(std::string id, std::string bookname,std::string type_user, bool V);
        int return_book(std::string id,std::string isbncode);
        void check_available(std::string id, std::string bookname);
        int calc_fine(std::string id,std::string type_user);
        void clear_fine_amount(std::string id,std::string type_user);
        
};
class Library{
    public:
    void display_menu();
    void login();
    void add_book(std::string id);
    void update_book(std::string id);
    void delete_book(std::string id);
};
class Account{
    public:
    std::string name;
        void Account_add(std::string id);
        void Account_update(std::string id);
        void Account_delete(std::string id);
        void Account_search(std::string id);
        void Account_clear_history(std::string id);
};
class Book{
    public:
    std::string title;
    std::string author;
    std::string isbn;
    std::string publication;
        int is_issued;
    void Book_request(std::string id,std::string bookname,std::string type_user);
    void Show_duedate(std::string isbn_no);

    
};
class Student : public User{
    public:
        int Fine_amount;
        void display_student_menu(std::string id);
};
class Faculty : public User{
    public:
        int Fine_amount;
    public:
        void display_facu_menu(std::string id);

};
class Librarian : public User{
    public:
        void display_lib_menu(std::string id);
        void see_all_users(std::string id);
        void see_all_books(std::string id);
        void add_user(std::string id);
        void update_user(std::string id);
        void delete_user(std::string id);        
        void see_issued_to_user(std::string id,std::string uid);
        void see_issued_book(std::string id,std::string isbn);
        
};
void Library :: display_menu(){
    char c;
    std::cout<<"---------------------------------------------------------------------\n";
    std::cout<<"\n\nWelcome to the library management system!\n\n";
    std::cout<<"1. Press 1 to log in : \n";
    std::cout<<"2. Press 2 to exit\n";
    std::cout<<"---------------------------------------------------------------------\n";
    std::cin>>c;
    if(c=='1'){ //logs in a user 
        Library l;
        l.login();
    }
    else{
        std::cout<<"Adios Amigos ! Powering Off!";
        exit(1);
    }
}
void Library :: login(){

    std::string id,password;
    std::cout<<"Enter your id : ";
    std::cin>>id;
    std::cout<<"Enter the password : ";
    std::cin>>password;
    std::vector<std::string> words_in_a_row;
    std::string line_in_csv,word;
    std::fstream file("all_users_data.csv",std::ios::in);
    int count=0;
    if(file.is_open()){
        while(getline(file,line_in_csv)){
            words_in_a_row.clear();
            std::stringstream str(line_in_csv);
            while(getline(str,word,',')) words_in_a_row.push_back(word);
            if(words_in_a_row[1]==id){
                count=1;
                if(words_in_a_row[2]==password){
                    count++;
                    break;
                }
                else{
                    while(password!=words_in_a_row[2]){
                        std::cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                        char c;
                        std::cin>>c;
                        if(c=='1'){
                            std::cout<<"Enter the password : ";
                            std::cin>>password;
                            if(password==words_in_a_row[2]) count++;
                        }
                        else if(c=='2'){
                            std::cout<<"Exiting...";
                            return;
                        }
                        else{
                            std::cout<<"Please enter a valid input.\n";
                        }
                    }
                    if(count==2) break;
                }
            }
            if(count==2) break;            
        }
        if(count==0){
            std::cout<<"User not found\n";
            Library l;
            l.display_menu();
        }
        if(count==2){

            Student s;
            Faculty f;
            Librarian l;

            if(words_in_a_row[3]=="1"){
                s.display_student_menu(words_in_a_row[1]);
            }
            else if(words_in_a_row[3]=="2"){
                f.display_facu_menu(words_in_a_row[1]);
            }
            else{
                l.display_lib_menu(words_in_a_row[1]);
            }
        }
    }
}
void Student :: display_student_menu(std::string id){
    Student s;
    Book b;
    Account a;
    char c;
    std::string S;
    int fine1=0,fine2=0;
    s.reserve_to_issue(id,"1");
    std::cout<<"---------------------------------------------------------------------\n";
    std::cout<<"\nStudent Menu\n";
    std::cout<<"Press 1 to see all the books\n";
    std::cout<<"Press 2 to view books issued by you\n";
    std::cout<<"Press 3 to check if a book is available for issue or not\n";
    std::cout<<"Press 4 to view the fine\n";
    std::cout<<"Press 5 to issue a book\n";
    std::cout<<"Press 6 to return a book\n";
    std::cout<<"Press 7 to clear your fine\n";
    std::cout<<"Press 8 to see borrow history\n";
    std::cout<<"Press c to clear history\n";
    std::cout<<"Press r to reserve book\n";
    std::cout<<"Press u to unreserve book\n";    
    std::cout<<"Press 9 to logout\n";
    std::cout<<"---------------------------------------------------------------------\n";
    std::cin>>c;
    std::string book_name,isbncode;
    fine2=s.calc_fine(id,"1");
    switch(c){
        case '1':
            s.see_all_books(id);
            s.display_student_menu(id);
            break;
        case '2':
            s.see_issued_books(id);
            s.display_student_menu(id);

            break;
        case '3':
        std::cout<<"Enter the name of the book you want to check : ";
        std::cin.ignore();
        
            getline(std::cin,book_name);
            
            s.check_available(id,book_name);
          
            s.display_student_menu(id);
            
            break;
        case '4':
            readfile("all_users_data.csv");
            for(int i=0;i<content.size();i++) if(content[i][1]==id){ fine1=stoi(content[i][4]);}
            std::cout<<"Current fine amount : Rupees "<<fine1+fine2<<std::endl;
            s.display_student_menu(id);
            break;
        case '5':
        readfile("all_users_data.csv");
        for(int i=0;i<content.size();i++) if(content[i][1]==id){ fine1=stoi(content[i][4]);}
        content.clear();
        if(fine1+fine2>0) std::cout<<"Clear fine first before borrowing more books !\n";
        else{
        std::cout<<"Enter the name of the book you want to issue : ";
        std::cin.ignore();
            getline(std::cin,book_name);
            s.issue_book(id,book_name,"1",false);
        }
            s.display_student_menu(id);            
            break;
        case '6':
        std::cout<<"Enter the isbn code of the book you want to return : ";
        std::cin>>isbncode;            
            content.clear();
            readfile("all_users_data.csv");
            content2=content;
            for(int i=0;i<content2.size();i++){ 
                if(content2[i][1]==id){ 
                    // std::cout<<"YES\n";
                    fine1=stoi(content2[i][4]); 
                    int v=-1;
                    v=s.return_book(id,isbncode);
                    if(v>-1) std::cout<<" Successfully returned\n";
                    fine1+=v;
                    content2[i][4]=std::to_string(fine1);
                    // content[i][4]="69";
                }
            }
            if (!content2.empty()) {  
                writefile(content2, "all_users_data.csv");  // Save updated content
            } else {
                std::cerr << "Error: Content is empty! Not writing to file.\n";
            }
            
            content.clear();
            s.display_student_menu(id);
            break;
        case '7':
            if(fine2>0) std::cout<<"Return the overdue books first before clearing fine"<<std::endl;
            else s.clear_fine_amount(id,"1");
            s.display_student_menu(id);
            break;
        case '8':
            s.see_history(id);
            s.display_student_menu(id);
            break;               
        case '9':
            logout();
            break;
        case ('c'):
            std::cout<<"Confirm History Deletion by typing Y :";
            char x;
            std::cin>>x;
            if(x=='y'||x=='Y'){
                a.Account_clear_history(id);
            }
            s.display_student_menu(id);
            break;
        case ('r'):
        std::cout<<"Enter name of the book You want to reserve :";
        std::cin>>S;
        s.reserve_book(id,S);
        break;
        case ('u'):
        std::cout<<"Enter name of the book You want to unreserve :";
        std::cin>>S;
        s.unreserve_book(id,S);
        break;
        // break;
        // case ('u'||'U'):
        // break;
    }
}

void Faculty :: display_facu_menu(std::string id){
    char c;
    Faculty f;
    Book b;
    Account a;
    std::string S;
    f.reserve_to_issue(id,"2");
    int Overdue=f.calc_fine(id,"2");
    std::cout<<"---------------------------------------------------------------------\n";
    std::cout<<"\nFaculty Menu\n";
    std::cout<<"Press 1 to see all the books\n";
    std::cout<<"Press 2 to view books issued by you\n";
    std::cout<<"Press 3 to check if a book is available for issue or not\n";
    std::cout<<"Press 4 to view number of overdue books\n";
    std::cout<<"Press 5 to issue a book\n";
    std::cout<<"Press 6 to return a book\n";
    std::cout<<"Press 7 to see borrow history\n";
    std::cout<<"Press c to clear history\n";
    std::cout<<"Press r to reserve book\n";
    std::cout<<"Press u to unreserve book\n";   
    std::cout<<"Press 8 to logout\n";
    std::cout<<"---------------------------------------------------------------------\n";
    std::cin>>c;
    std::string book_name,isbncode;
    switch(c){
        case '1':
            f.see_all_books(id);
            f.display_facu_menu(id);
            break;
        case '2':
            f.see_issued_books(id);
            f.display_facu_menu(id);
            break;
        case '3':
        std::cout<<"Enter the name of the book you want to check : ";
        std::cin>>book_name;
            f.check_available(id,book_name);
            f.display_facu_menu(id);
            break;
        case '4':
            Overdue=f.calc_fine(id,"2");
            std::cout<<"You have "<<Overdue<<" overdue books!\n";
            f.display_facu_menu(id);
            break;
        case '5':
        if(Overdue) std::cout<<"Return all overdue books before borrowing a new book!\n";
        else{
        std::cout<<"Enter the name of the book you want to issue : ";
        std::cin>>book_name;
            f.issue_book(id,book_name,"2",false);
        }
            f.display_facu_menu(id);            
            break;
        case '6':
        std::cout<<"Enter the isbn code of the book you want to return : ";
        std::cin>>isbncode;            
            content.clear();
            readfile("all_users_data.csv");
            content2=content;
            for(int i=0;i<content2.size();i++){ 
                if(content2[i][1]==id){ 
                    // std::cout<<"YES\n"; 
                    int v=-1;
                    v=f.return_book(id,isbncode);
                    if(v>-1) std::cout<<" Successfully returned\n";
                    // fine1+=10;
                    Overdue=f.calc_fine(id,"2");
                    content2[i][4]=std::to_string(Overdue);
                    // content[i][4]="69";
                }
            }
            if (!content2.empty()) {  
                writefile(content2, "all_users_data.csv");  // Save updated content
            } else {
                std::cerr << "Error: Content is empty! Not writing to file.\n";
            }
            
            content.clear();
            f.display_facu_menu(id);
            break;
            case '7':
            f.see_history(id);
            f.display_facu_menu(id);
            break;
            break;
        case '8':
            logout();
            break;
            case ('c'):
            std::cout<<"Confirm History Deletion by typing Y :";
            char x;
            std::cin>>x;
            if(x=='y'||x=='Y'){
                a.Account_clear_history(id);
            }
            f.display_facu_menu(id);
            break;
        case ('r'):
        std::cout<<"Enter name of the book You want to reserve :";
        std::cin>>S;
        f.reserve_book(id,S);
        f.display_facu_menu(id);
        break;
        case ('u'):
        std::cout<<"Enter name of the book You want to unreserve :";
        std::cin>>S;
        f.unreserve_book(id,S);
        f.display_facu_menu(id);
        break;
    }
}

void User :: see_history(std::string id){
    content.clear();
    int count=1;
    readfile("borrow_history.csv");
    std::cout<<"Format: Serial No./ Name/ ISBN/ Year of Publish/ Date of Borrow/Date of Return\n";
    for(int i=0;i<content.size();i++){
        if(content[i][0]==id){
            std::cout<<count<<". ";
            count++;
            for(int k=1;k<content[i].size()-2;k++) std::cout<<content[i][k]<<" | ";
            time_t stamp = stoi(content[i][5]);
            tm *dateformat = localtime(&stamp);  
            std::cout<< dateformat->tm_mday<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<" | ";
            int K=stoi(content[i][6]);
            if(K==0){
                std::cout<<"On Loan\n";
            }
                else{
            time_t stamp = stoi(content[i][6]);
            tm *dateformat = localtime(&stamp);  
            std::cout<< dateformat->tm_mday<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<"\n";
        }
        }
    }
    content.clear();
}
void Account :: Account_clear_history(std::string id){
    content.clear();
    content2.clear();
    bool v=false;
    readfile("borrow_history.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][0]==id){v=true; continue;}
        content2.push_back(content[i]);
    }
    content.clear();
    writefile(content2,"borrow_history.csv");
    content2.clear();
    std::cout<<(v?"Account History Has Been Cleared! \n":"Account Doesn't Exist, OR There is no History! \n");
}
void User :: see_all_books(std::string id){
    content.clear();
    std::cout<<"In the data below, 0 signifies that the book is not issued and 1 means that the book is issued.\n";
    readfile("all_books_data.csv");
    printdata(content);
    content.clear();
}
void User :: issue_book(std::string id,std::string bookname,std::string type_user,bool V){
    content.clear();
    int fl=0;
    //fl variable finds the first instance of an unborrowed book title.
    if(type_user=="1"){
        int count=0;
        content.clear();
        readfile("issued_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==id){
                count++;
            }
        }
        content.clear();
        if(count>2){
            std::cout<<"You have issued max number of books! Return a book before borrowing another one. \n\n";
            readfile("all_books_data.csv");
            for(int i=0;i<content.size();i++) if(content[i][0]==bookname && content[i][5]=="3") content[i][5]="0";
            writefile(content,"all_books_data.csv");
            content.clear();
            
        }
        else{
            content.clear();
            readfile("all_books_data.csv");
            // std::cout<<content.size()<<std::endl;            
            for(int i=0;i<content.size();i++){                
                //V allows bypass for the user who had reserved a book.
                if(fl==0 && content[i][0]==bookname && (content[i][5]=="0" || V)){
                    fl=1;
                    std::cout<<"Book is available!\n";
                    content[i][5]="1";
                    toupdate.clear();
                    toupdate.push_back(id);
                    toupdate.push_back(bookname);
                    toupdate.push_back(content[i][1]);
                    toupdate.push_back(content[i][3]);
                    toupdate.push_back(content[i][4]);
                    // toupdate.push_back(content[i][5]);
                    toupdate.push_back(std::to_string(time(0)));
                    std::vector<std::string> Y(toupdate); // Copy existing vector X
                    Y.push_back("No_One");
                    writefileappend(Y,"issued_books_data.csv");
                    toupdate.push_back(std::to_string(0));
                    writefileappend(toupdate,"borrow_history.csv");
                    std::cout<<"Book succesfully issued\n";
                    break;
                }
            }
            if(fl==0) std::cout<<"Book not available\n";
            writefile(content,"all_books_data.csv");
            content.clear();
        }
    }
    if(type_user=="2"){
        int count=0;
        content.clear();
        readfile("issued_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==id){
                count++;
            }
        }
        content.clear();
        if(count>4){
            std::cout<<"You have issued max number of books! Return a book before borrowing another one. \n\n";
            readfile("all_books_data.csv");
            for(int i=0;i<content.size();i++) if(content[i][0]==bookname && content[i][5]=="3") content[i][5]="0";
            content.clear();
        }
        else{
            content.clear();
            readfile("all_books_data.csv");
            // std::cout<<content.size()<<std::endl;  
            
            for(int i=0;i<content.size();i++){                
                //V allows bypass for the user who had reserved a book.
                if(fl==0 && content[i][0]==bookname && (content[i][5]=="0" || V)){
                    fl=1;
                    std::cout<<"Book is available!\n";
                    content[i][5]="1";
                    toupdate.clear();
                    toupdate.push_back(id);
                    toupdate.push_back(bookname);
                    toupdate.push_back(content[i][1]);
                    toupdate.push_back(content[i][3]);
                    toupdate.push_back(content[i][4]);
                    // toupdate.push_back(content[i][5]);
                    toupdate.push_back(std::to_string(time(0)));
                    std::vector<std::string> Y(toupdate); // Copy existing vector X
                    Y.push_back("No_One");
                    writefileappend(Y,"issued_books_data.csv");
                    toupdate.push_back(std::to_string(0));
                    writefileappend(toupdate,"borrow_history.csv");
                    std::cout<<"Book succesfully issued\n";
                    break;
                }
            }
            if(fl==0) std::cout<<"Book not available\n";
            writefile(content,"all_books_data.csv");
            content.clear();
        }
    }
}
int User :: return_book(std::string id,std::string isbncode){
    content.clear();
    int fl=0;
    readfile("issued_books_data.csv");
    
    for(int i=0;i<content.size();i++){
   

        if(content[i][3]==isbncode && content[i][0]==id){
            fl=1;
            if(content[i][6]=="No_One") content.erase(content.begin()+i,content.begin()+i+1);
            else content[i][0]="No_One";
            
            std::cout<<"Book was issued by you and is now being returned\n";
            writefile(content,"issued_books_data.csv");
            content.clear();
            readfile("all_books_data.csv");
            for(int i=0;i<content.size();i++){
                if(content[i][3]==isbncode) content[i][5]=(content[i][5]=="1"?"0":"3");
            }
            writefile(content,"all_books_data.csv");
            break;
        }
    }
    
    content.clear();
    if(fl==0){ std::cout<<"Invalid details!\n"; content.clear(); return 0;}
    content.clear();
    int P,Q;
    readfile("borrow_history.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][3]==isbncode && content[i][0]==id){
            // std::cout<<"OK\n";
            if(content[i][6]=="0"){ content[i][6]=std::to_string(time(0));P=stoi(content[i][5]);Q=stoi(content[i][6]);}
            
        }
    }
    writefile(content,"borrow_history.csv");
    content.clear();
    // std::cout<<P<<" borrow\n"<<Q<<" return\n";
    if((int)((Q-P)/86400) > 15){
        std::cout<<"You have incurred some fine. Please pay it\n";
         return (10*((int)((Q-P)/86400) - 15));}
    else return 0;
}
void User :: see_issued_books(std::string id){
    int count=0;
    content.clear();
    
    readfile("issued_books_data.csv");
    // if(content.size()==0) std::cout<<"WOW";
    for(int i=0;i<content.size();i++){
        if(content[i][0]==id){
            count++;
            std::cout<<count<<". ";
            
            for(int k=1;k<5;k++)
            std::cout<<content[i][k]<<" | ";
            time_t stamp = stoi(content[i][5]);
            tm *dateformat = localtime(&stamp);  
            std::cout<< dateformat->tm_mday<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<"\n";
        }
    }
    if(count==0) std::cout<<"You haven't issued any books as of now\n\n";
    content.clear();
}
void User :: check_available(std::string id,std::string bookname){
    content.clear();
    int fl=0;
    readfile("all_books_data.csv");
    int count=1;
    for(int i=0;i<content.size();i++){
        if(content[i][0]==bookname && content[i][4]=="0"){
            fl=1;
            std::cout<<count<<". ";
            count++;
            std::cout<<"Book is available!\n";
            for(auto j:content[i])
            std::cout<<j<<" | ";
            std::cout<<"\n";
            break;
        }
    }
    if(fl==0) std::cout<<"Book not available\n";
    content.clear();
}
int User :: calc_fine(std::string id, std::string type_user){
    int fine=0;
    if(type_user=="1"){
        content.clear();
        readfile("issued_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==id){
                int curtime = time(0);
                int isstime = stoi(content[i][5]);
                if((curtime-isstime)/86400>15) fine+=10*((curtime-isstime)/86400 - 15);
            }
        }
        content.clear();
        return fine;
        
    }
    if(type_user=="2"){
        content.clear();
        readfile("issued_books_data.csv");
        for(int i=0;i<content.size();i++){
            if(content[i][0]==id){
                int curtime = time(0);
                int isstime = stoi(content[i][5]);
                if((curtime-isstime)/86400>60) fine+=1;
            }
        }
        content.clear();
        return fine;
    }
}
void User :: logout(){
    std::cout<<"Logging out...\n";
    Library l;
    l.display_menu();
}
void User :: clear_fine_amount(std::string id,std::string type_user){
    int fine, a = calc_fine(id,type_user);
    content.clear();
    readfile("all_users_data.csv");
    for(int i=0;i<content.size();i++) if(content[i][1]==id){ fine=stoi(content[i][4]);}
    a+=fine;
    if(a==0) std::cout<<"You have no pending dues\n";
    else{ std::cout<<"Your fine of Rupees "<<a<<" is being cleared.\n";
        for(int i=0;i<content.size();i++) if(content[i][1]==id) content[i][4]="0";
        writefile(content,"all_users_data.csv");
    }

    content.clear();
}
void User :: reserve_book(std::string id,std::string bookname){
    readfile("all_books_data.csv");
    for(int i=0;i<content.size();i++) if(content[i][0]==bookname){
        if(content[i][5]=="1"){ content[i][5]="2";
            writefile(content,"all_books_data.csv");
            content.clear();
            readfile("issued_books_data.csv");
            for(int i=0;i<content.size();i++) if(content[i][1]==bookname) content[i][6]=id;
            writefile(content,"issued_books_data.csv");
            std::cout<<"The book has successfully been reserved !\n";
        }
            else std::cout<<"The book has already been reserved !\n";}
    content.clear();
}
void User :: unreserve_book(std::string id,std::string bookname){
    readfile("all_books_data.csv");
    for(int i=0;i<content.size();i++) if(content[i][0]==bookname && content[i][5]=="2") content[i][5]="1";
    writefile(content,"all_books_data.csv");
    content.clear();
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++) if(content[i][1]==bookname && content[i][6]==id) content[i][6]="No_One";
    writefile(content,"issued_books_data.csv");
    content.clear();
}
void User:: reserve_to_issue(std::string id,std::string type){
    content.clear();
    content2.clear();
    readfile("issued_books_data.csv");
    content2=content;
    content.clear();
    for(int i=0;i<content2.size();i++){
        if(content2[i][0]=="No_One" && content2[i][6]==id){
            std::cout<<"Issuing book : "<<content2[i][1]<<std::endl;
            issue_book(id,content2[i][1],type,true);                     
        }
    }
    content.clear();
    content2.clear();
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][0]=="No_One" && content[i][6]==id) continue;
        content2.push_back(content[i]);
    }
    writefile(content2,"issued_books_data.csv");
    content2.clear();
    content.clear();
}

void Book :: Show_duedate(std::string isbn){
    content.clear();
    std::string uid;
    time_t stamp;
    readfile("issued_books_data.csv");
    int fl=0;
    for(int i=0;i<content.size();i++){
        if(content[i][2]==isbn){
            fl=1;
            uid = content[i][0];
            stamp = stoi(content[i][3]);
            break;
        }
    }
    content.clear();
    int days=30;
    readfile("all_users_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][1]==uid){
            if(content[i][3]=="1")
                days=15;                                                                                                                        
            else
                days=30;
            break;
        }
    }
    stamp+=days*86400;
    tm *due_time = localtime(&stamp);  
    if(fl==0) std::cout<<"Book was not issued!\n";
    else{
        std::cout<<"Due date of the book is : ";
        std::cout<< due_time->tm_mday<<"/"<<1 + due_time->tm_mon<<"/"<<1900 + due_time->tm_year<<"\n";
    }
}
void Book :: Book_request(std::string id,std::string bookname,std::string type_user){
    User u;
    u.issue_book(id,bookname,type_user,false);
}



void Librarian :: display_lib_menu(std::string id){
    std::cout<<"---------------------------------------------------------------------\n";
    std::cout<<"\nWelcome "<<id<<"! You are logged in as librarian.\n\n";
    std::cout<<"Press 1 to add a user\n";
    std::cout<<"Press 2 to update a user\n";
    std::cout<<"Press 3 to delete a user\n";
    std::cout<<"Press 4 to add a book\n";
    std::cout<<"Press 5 to update a book\n";
    std::cout<<"Press 6 to delete a book\n";
    std::cout<<"Press 7 to see all books issued to a particular user\n";
    std::cout<<"Press 8 to see which book is issued to which user\n";
    std::cout<<"Press 9 to view all users\n";
    std::cout<<"Press 0 to view all books\n";
    std::cout<<"Press d to show due date of a book\n";
    std::cout<<"Press c to clear a user's history\n";
    std::cout<<"Press l to logout\n";
    std::cout<<"---------------------------------------------------------------------\n";
    char c;
    std::cin>>c;
    Librarian l;
    Library L;
    Account a;
    Book b;
    std::string S;
    User u;
    std::string isbn,uid;
    switch(c){
        case '1':
            a.Account_add(id);
            l.display_lib_menu(id);
            break;
        case '2':
            a.Account_update(id);
            l.display_lib_menu(id);
            break;
        case '3':
            a.Account_delete(id);
            l.display_lib_menu(id);
            break;
        case '4':
            L.add_book(id);
            l.display_lib_menu(id);
            break;
        case '5':
            L.update_book(id);
            l.display_lib_menu(id);
            break;
        case '6':
            L.delete_book(id);
            l.display_lib_menu(id);
            break;
        case '7':
        std::cout<<"Enter the id of the user : ";
            std::cin>>uid;
            l.see_issued_to_user(id,uid);
            l.display_lib_menu(id);
            break;
        case '8':
        std::cout<<"Enter the isbn number of the book : ";
        std::cin>>isbn;
            l.see_issued_book(id,isbn);
            l.display_lib_menu(id);
            break;
        case '9':
            l.see_all_users(id);
            l.display_lib_menu(id);
            break;
        case '0':
            l.see_all_books(id);
            l.display_lib_menu(id);
            break;
        case 'd':
        std::cout<<"Enter the isbn number of the book : ";
        std::cin>>isbn;
            b.Show_duedate(isbn);
            l.display_lib_menu(id);
            break;
            case ('c'):
            std::cout<<"Enter user's Username for history deletion :";
            
            std::cin>>S;
            a.Account_clear_history(S);            
            l.display_lib_menu(id);
            break;
        case 'l':
            logout();
            l.display_lib_menu(id);
            break;
    }
}

void Librarian :: see_all_users(std::string id){
    content.clear();
    readfile("all_users_data.csv");
    std::cout<<"Below are all the users. 1 at the end signifies a student, 2 means a faculty and 3 means a librarian \n\n";
    std::cout<<"The data is given in the form of student,username,type of user.\n\n";
    printdata_notpassword(content);
    content.clear();
}
void Librarian :: see_all_books(std::string id){
    content.clear();
    readfile("all_books_data.csv");
    std::cout<<"Below are all the books. 1 at the end signifies a student, 2 means a faculty and 3 means a librarian \n\n";
    std::cout<<"The data is given in the form of book name,author,pubisher,isbn number,and is_issued(1 if book is issued).\n\n";
    printdata(content);
    content.clear();
}
void Account :: Account_add(std::string id){
    std::cout<<"Please enter the details of the new user : \n";
    std::string _name,_id,_password,_type;
    std::cout<<"Enter name: ";
    std::cin.ignore();
    getline(std::cin,name);
    std::cout<<"Enter id : ";
    std::cin>>_id;
    std::cout<<"Enter password : ";
    std::cin>>_password;
    std::cout<<"Enter type of the user : 1 if student, 2 if faculty, 3 if librarian : ";
    std::cin>>_type;
    std::fstream fout("all_users_data.csv",std::ios::out | std::ios::app);
    fout<<name<<","<<_id<<","<<_password<<","<<_type<<","<<"0"<<'\n';
    std::cout<<"New user has been added.\n";
}
void Library :: add_book(std::string id){
    std::cout<<"Please enter the details of the new book : \n";
    std::string title,author,isbn,publisher;
    std::cout<<"Enter title: ";
    std::cin.ignore();
    getline(std::cin,title);
    std::cout<<"Enter author : ";
    std::cin>>author;
    std::cout<<"Enter isbn : ";
    std::cin>>isbn;
    std::cout<<"Enter name of publisher : ";
    std::cin>>publisher;
    std::fstream fout("all_books_data.csv",std::ios::out | std::ios::app);
    fout<<title<<","<<author<<","<<isbn<<","<<publisher<<",0"<<'\n';
    std::cout<<"New book has been added.\n";
}
void Library :: delete_book(std::string id){
    std::string isbnno;
    std::cout<<"Enter the isbn number of the book : ";
    std::cin>>isbnno;
    content.clear();
    int found=0;
    readfile("all_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][3]==isbnno){
            found=1;
            content.erase(content.begin()+i,content.begin()+i+1);
            break;
        }
    }
    writefile(content,"all_books_data.csv");
    content.clear();
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][2]==isbnno){
            content.erase(content.begin()+i,content.begin()+i+1);
            break;
        }
    }
    writefile(content,"issued_books_data.csv");
    content.clear();
    if(found==0) std::cout<<"Book not found.\n";
}
void Account :: Account_delete(std::string id){
    std::string uid;
    std::cout<<"Enter the user id of the user : ";
    std::cin>>uid;
    content.clear();
    int found=0;
    readfile("all_users_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][1]==uid){
            found=1;
            content.erase(content.begin()+i,content.begin()+i+1);
            break;
        }
    }
    writefile(content,"all_users_data.csv");
    content.clear();
    std::vector<std::string> isbns;
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][0]==uid){
            isbns.push_back(content[i][2]);
            content.erase(content.begin()+i,content.begin()+i+1);
            break;
        }
    }
    writefile(content,"issued_books_data.csv");
    content.clear();

    readfile("all_books_data.csv");
    for(int i=0;i<content.size();i++){
        for(int j=0;j<isbns.size();j++){
            if(isbns[j]==content[i][3]){
                content[i][4]="0";
            }
        }
    }
    writefile(content,"all_books_data.csv");
    if(found==0) std::cout<<"User not found.\n";
}
void Account :: Account_update(std::string id){
    std::string upid;
    std::cout<<"Enter the id of the user you want to update : ";
    std::cin>>upid;
    std::cout<<"Enter the serial number of the field you want to update : \n";
    std::cout<<"1. Password\n";
    std::cout<<"2. Name of the User\n";
    std::cout<<"3. Status of the User\n";
    char c;
    std::cin>>c;
    content.clear();
    int fl=0;
    readfile("all_users_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][1]==upid){
            fl=1;
            std::string new_field;
            std::cout<<"Enter the new value of the field : ";
            std::cin.ignore();
            getline(std::cin,new_field);
            if(c=='1'){
                content[i][2]=new_field;
            }
            else if(c=='2'){
                content[i][0]=new_field;
            }
            else if(c=='3'){
                content[i][3]=new_field;
                if(content[i][3]=="3") content[i][4]="0";
            }
            else{
                std::cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    std::cout<<"User updated\n";
    writefile(content,"all_users_data.csv");
    content.clear();
    if(fl==0) std::cout<<"User was not found.\n\n";
}
void Library :: update_book(std::string id){
    std::string isbn_no;
    std::cout<<"Enter the isbn number of the book you want to update : ";
    std::cin>>isbn_no;
    std::cout<<"Enter the serial number of the field you want to update : \n";
    std::cout<<"1. Name of the Book\n";
    std::cout<<"2. Name of the Author\n";
    std::cout<<"3. Name of the Publisher\n";
    char c;
    std::cin>>c;
    content.clear();
    int fl=0;
    std::string new_field;
    readfile("all_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][3]==isbn_no){
            fl=1;
            std::cout<<"Enter the new value of the field : ";
            std::cin.ignore();
            getline(std::cin,new_field);
            if(c=='1'){
                content[i][0]=new_field;
            }
            else if(c=='2'){
                content[i][1]=new_field;
            }
            else if(c=='3'){
                content[i][2]=new_field;
            }
            else{
                std::cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    writefile(content,"all_books_data.csv");
    content.clear();
    
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][2]==isbn_no){
            fl=1;
            if(c=='1'){
                content[i][1]=new_field;
            }
            break;
        }
    }
    std::cout<<"Book updated\n";
    writefile(content,"issued_books_data.csv");

    if(fl==0) std::cout<<"Book was not found.\n\n";
}
void Librarian :: see_issued_to_user(std::string id,std::string uid){
    std::vector <std::string> isbns;
    content.clear();
    int count=1;
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++){
        if(content[i][0]==uid){
            isbns.push_back(content[i][2]);
        }
    }
    content.clear();
    if(isbns.size()==0) std::cout<<"No book is issued to this user.\n\n";
    else{
        readfile("all_books_data.csv");
        for(int d=0;d<isbns.size();d++){
            for(int i=0;i<content.size();i++){
                if(content[i][3]==isbns[d]){
                    std::cout<<count<<". ";
                    count++;
                    for(auto y:content[i]){
                        if(y!=content[i].back())
                        std::cout<<y<<" | ";
                        else
                        std::cout<<y<<"\n";
                    }
                }
            }
        }
        content.clear();
    }
}
void Librarian :: see_issued_book(std::string id,std::string isbn){
    content.clear();
    int coun=0;
    readfile("issued_books_data.csv");
    for(int i=0;i<content.size();i++){
        coun=1;
        if(content[i][2]==isbn){
            std::cout<<"Book with id "<<isbn<<" and name "<<content[i][1]<<" is issued to user with id : "<<content[i][0]<<"\n";
        }
    }
    if(coun==0) std::cout<<"Book has not been issued to anyone.\n\n";
}

int main(){
    Library start;
    start.display_menu();
    return 0;
}