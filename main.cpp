#include <iostream>
    #include <vector>
    #include <fstream>
    #include <map>
    #include <ctime>
    #include <string>
    #include <cstring>
    using namespace std;
    
    #define monthstart 1
    
    class employee {
    private:
        string name;
        string employee_id;
        double salary;
        double sal;
        short int works;
        time_t intime;
        bool io;
    
    public:
        employee(): salary(0), sal(0), works(0), intime(0), io(false) {}
    
        string getName() const { return name; }
        void setName(const string &_name) { name = _name; }
    
        string getEmployeeId() const { return employee_id; }
        void setEmployeeId(const string &_employee_id) { employee_id = _employee_id; }
    
        double getSalary() const { return salary; }
        void setSalary(double _salary) { salary = _salary; }
    
        double getSal() const { return sal; }
        void setSal(double _sal) { sal = _sal; }
    
        short int getWorks() const { return works; }
        void setWorks(short int _works, char a) { works = _works; }
        void setWorks(short int _works) { works = works + _works; }
    
        time_t getIntime() const { return intime; }
        void setIntime(time_t _intime) { intime = _intime; }
    
        bool getIO() const { return io; }
        void setIO(bool _io) { io = _io; }
    };
    
    class File {
    public:
        map<string, employee> emp;
    
        File() {
            ifstream fin("file1.txt");
            employee temp;
            string name, id, sala;
            while (fin >> id >> ws && fin >> sala >> ws && getline(fin, name)) {
                temp.setName(name);
                temp.setEmployeeId(id);
                int n = stoi(sala);
                temp.setSal(n);
                emp[id] = temp;
            }
            fin.close();
        }
    
        bool ismonthstart() {
            time_t current_time = time(NULL);
            tm *ltm = localtime(&current_time);
            int m = 1 + ltm->tm_mon;
            int y = 1900 + ltm->tm_year;
            string filename = to_string(m) + "_" + to_string(y) + ".txt";
            ifstream fin(filename.c_str());
            if (fin) {
                fin.close();
                return false;
            } else {
                ofstream fout(filename.c_str());
                for (auto it = emp.begin(); it != emp.end(); ++it) {
                    fout << it->second.getName() << " " << it->second.getSalary() << endl;
                }
                fout.close();
                return true;
            }
        }
    };
    
    class times {
    public:
        time_t current_time;
        string ch;
        times() {}
    
        string ist() {
            current_time = time(NULL);
            tm *ltm = localtime(&current_time);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
            ch = buffer;
            return ch;
        }
    
        int get_year() {
            string t = ist();
            return (t[0] - 48) * 1000 + (t[1] - 48) * 100 + (t[2] - 48) * 10 + (t[3] - 48);
        }
    
        int get_month() {
            string t = ist();
            return (t[5] - 48) * 10 + (t[6] - 48);
        }
    
        int get_date() {
            string t = ist();
            return (t[8] - 48) * 10 + (t[9] - 48);
        }
    
        int get_hours() {
            string t = ist();
            return (t[11] - 48) * 10 + (t[12] - 48);
        }
    
        int get_min() {
            string t = ist();
            return (t[14] - 48) * 10 + (t[15] - 48);
        }
    
        int get_seconds() {
            string t = ist();
            return (t[17] - 48) * 10 + (t[18] - 48);
        }
    };
    
    times Times;
    
    class process : public File {
    public:
        process() {}
    
        bool isdayend() {
            return (Times.get_hours() == 23 && Times.get_min() == 59);
        }
    
        void axcess() {
            while (true) {
                string empl;
                cout << "Enter your employee id: ";
                string input;
                getline(cin, input);
                if (!input.empty()) {
                    empl = input;
                    auto it = emp.find(empl);
                    if (it == emp.end()) {
                        cout << "Enter a valid employee id." << endl;
                        continue;
                    }
    
                    employee &temp = emp[empl];
                    if (temp.getIO()) {
                        cout << "You are leaving the office at " << Times.ist() << endl;
                        time_t current_time = time(NULL);
                        short int duration = difftime(current_time, temp.getIntime());
                        temp.setWorks(duration);
                        cout << "Total work duration: " << temp.getWorks() << " seconds." << endl;
                        temp.setIO(false);
                    } else {
                        cout << "You are entering the office at " << Times.ist() << endl;
                        time_t current_time = time(NULL);
                        temp.setIntime(current_time);
                        temp.setIO(true);
                    }
                } else {
                    if (ismonthstart()) {
                        cout << "It's the start of the month." << endl;
                    }
    
                    if (isdayend()) {
                        cout << "It's the end of the day." << endl;
                        time_t current_time = time(NULL);
                        tm *ltm = localtime(&current_time);
                        int m = 1 + ltm->tm_mon;
                        int y = 1900 + ltm->tm_year;
                        string filename = to_string(m) + "_" + to_string(y) + ".txt";
                        ofstream fout(filename.c_str());
                        for (auto it = emp.begin(); it != emp.end(); ++it) {
                            fout << it->second.getName() << " " << it->second.getSalary() << endl;
                        }
                        fout.close();
                    }
                }
            }
        }
    };
    
    int main() {
        process tracking;
        tracking.axcess();
        return 0;
    }
    
