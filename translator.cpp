#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stack>


using namespace std;

enum type_of_lex
{
 PROGRAM, AND, OR, NOT, TRUE, FALSE, ELSE, IF, INT, READ, WHILE, WRITE, FOR, STRING, BOOL, DO, GOTO, LABEL,//17
 FINAL, SEMICOLON, COMMA, COLON, L_BRACKET, R_BRACKET, L_C_BRACKET, R_C_BRACKET, PLUS, MIN, MUL, SLASH, //28
 EQ, NEQ, LS, GE, LEQ, GEQ, TWOEQUAL, PERCENT, QUOTES,//38
 CONST_STR, CONST_INT, CONST_BOOL, IDENTIFIER, NULLP, //43
 POLIZ_GO, POLIZ_FGO, POLIZ_LABEL, POLIZ_ADDRESS//47
};

enum type_of_ident { INT_VAR, BOOL_VAR, STR_VAR };

enum type_of_expression { num, str };

void print_type(type_of_lex t)
{
    if (t == PROGRAM) cout << "PROGRAM"; else if (t == AND) cout << "AND"; else if (t == OR) cout << "OR";
    else if (t == NOT) cout << "NOT"; else if (t == TRUE) cout << "TRUE"; else if (t == FALSE) cout << "FALSE"; else if (t == ELSE) cout << "ELSE";
    else if (t == IF) cout << "IF"; else if (t == INT) cout << "INT"; else if (t == READ) cout << "READ"; else if (t == WHILE) cout << "WHILE";
    else if (t == WRITE) cout << "WRITE"; else if (t == FOR) cout << "FOR"; else if (t == STRING) cout << "STRING"; else if (t == BOOL) cout << "BOOL";
    else if (t == DO) cout << "DO"; else if (t == LABEL) cout << "LABEL"; else if (t == GOTO) cout << "GOTO"; else if (t == FINAL) cout << "FINAL";
    else if (t == SEMICOLON) cout << "SEMICOLON"; else if (t == COMMA) cout << "COMMA"; else if (t == COLON) cout << "COLON"; else if (t == L_BRACKET) cout << "L_BRACKET";
    else if (t == R_BRACKET) cout << "R_BRACKET"; else if (t == PLUS) cout << "PLUS"; else if (t == MIN) cout << "MIN"; else if (t == MUL) cout << "MUL";
    else if (t == SLASH) cout << "SLASH"; else if (t == EQ) cout << "EQ"; else if (t == NEQ) cout << "NEQ"; else if (t == LS) cout << "LS";
    else if (t == GE) cout << "GE"; else if (t == LEQ) cout << "LEQ"; else if (t == GEQ) cout << "GEQ"; else if (t == TWOEQUAL) cout << "TWOEQUAL";
    else if (t == L_C_BRACKET) cout << "L_C_BRACKET"; else if (t == R_C_BRACKET) cout << "R_C_BRACKET"; else if (t == PERCENT) cout << "PERCENT";
    else if (t == QUOTES) cout << "QUOTES"; else if (t == CONST_STR) cout << "CONST_STR"; else if (t == CONST_BOOL) cout << "CONST_BOOL"; else if (t == CONST_INT) cout << "CONST_INT";
    else if (t == IDENTIFIER) cout << "IDENTIFIER"; else if (t == NULLP) cout << "NULLP"; else if (t == POLIZ_GO) cout << "POLIZ_GO"; else if (t == POLIZ_FGO) cout << "POLIZ_FGO";
    else if (t == POLIZ_LABEL) cout << "POLIZ_LABEL"; else if (t == POLIZ_ADDRESS) cout << "POLIZ_ADRESS";
}

//---------------------------------------------------------------------------------------------------------



class Ident {
    string name;
    bool initialization;
    bool declared;

    type_of_lex type;
    type_of_ident type_of_id;

    int int_val;
    string str_val;
    double bool_val;

public:
    // Ident() { initialization = false; declared = false; }

    explicit Ident(const string &n):name(n), initialization(false), declared(false) {}

    explicit Ident(const string &n, int val):name(n), int_val(val), initialization(false), declared(false) {}

    explicit Ident(const string &n, string val):name(n), str_val(val), initialization(false), declared(false) {}

    explicit Ident(const string &n, bool val):name(n), bool_val(val), initialization(false), declared(false) {}


    string get_name () const { return name; }
     bool operator== (const string& s) const { return name == s; }

 type_of_lex get_type () { return type; }
    void set_type ( type_of_lex t ) { type = t; }

 type_of_ident get_type_of_id () { return type_of_id; }
    void set_type_of_id ( type_of_ident t ) { type_of_id = t; }

 string get_str_value () const {if (type_of_id == STR_VAR) return str_val; else { string err = "Trying to get str value from not str variable!"; throw err;}}
    int get_int_value () const {if (type_of_id == INT_VAR) return int_val; else { string err = "Trying to get int value from not int variable!"; throw err;}}
    double get_bool_value () const {if (type_of_id == BOOL_VAR) return bool_val; else { string err = "Trying to get bool value from not bool variable!"; throw err;}}

    void set_value (int v) { int_val = v; }
    void set_value (double v) { bool_val = v; }
    void set_value (string v) { str_val = v; }

    bool get_declare() const { return declared; }
    void set_declare() {declared = true;}

    bool get_init () const { return initialization; }
    void set_init () { initialization = true; }



    friend ostream& operator << (ostream&s, Ident i)
    {
        s << "name - " << i.name << ", declared - " << i.declared << ", initialized - " << i.initialization;
        if (i.get_init()) {
 s << ", value - ";
            switch (i.type_of_id) {
                case INT_VAR:
 s << i.int_val;
                    break;
                case BOOL_VAR:
 s << i.bool_val;
                    break;
                case STR_VAR:
 s << i.str_val;
                    break;
            }
        }
        return s;
    }
};

//---------------------------------------------------------------------------------------------------------
template <class T, int max_size>  class Stack
{
 T s[max_size];
    int top;
public:
    Stack() {top = 0;}
    void reset() { top = 0;}
    bool is_full() {return top == max_size;}
    bool is_empty() {return top == 0;}

    void push(T i)
    {
        if (!is_full())
        {
            s[top] = i;
            top++;
        } else throw "stack is full!";
    }

    T pop()
    {
        if (!is_empty())
        {
            --top;
            return s[top];
        } else throw "stack is empty!";
    }

};

//---------------------------------------------------------------------------------------------------------

class Label {
    string name = "noname";
    int line;
    bool declared = false;

public:

    explicit Label(const string &n, int line): name(n), line(line){}

    bool operator== (const string& s) const { return name == s; }

    void set_line(int line)
    {
        this->line = line;
    }
    int get_line() const
    {
        return line;
    }
    string get_name() const
    {
        return name;
    }

    bool get_declared() {return declared;}
    
    //bool set_declared() {declared = true;}
    void set_declared() {declared = true;}


    friend ostream& operator << (ostream&s, Label l)
    {
        s << "label - " << l.name << ", to line - " << l.line;
        return s;
    }
};



//---------------------------------------------------------------------------------------------------------

vector <Ident> table_of_ident;

int put_ident (const string & buf)
{
    vector <Ident> :: iterator k;
    if ((k = find(table_of_ident.begin(), table_of_ident.end(), buf)) != table_of_ident.end())
        return k - table_of_ident.begin();
    table_of_ident.push_back(Ident(buf));
    return (int)table_of_ident.size() - 1;
}

vector <Label> table_of_label;


int put_label (const string & buf, int line)
{
    vector <Label> :: iterator k;
    if ((k = find(table_of_label.begin(), table_of_label.end(), buf)) != table_of_label.end())
        if (k->get_declared()) throw "Label already declared";
        else { k->set_declared(); return k - table_of_label.begin(); }
    else {
        table_of_label.push_back(Label(buf, line));
        return (int) table_of_label.size() - 1;
    }
}

int find_label (const string & buf)
{
    vector <Label> :: iterator k;
    if ((k = find(table_of_label.begin(), table_of_label.end(), buf)) != table_of_label.end()) {
        return (k - table_of_label.begin() + 1);
    }
    else return 0;
}




//-----------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------

class Lexeme {
    type_of_lex type;
    int number;
    string name = "noname";

public:

    int int_val;
    string str_val;
    double bool_val;

    explicit Lexeme( type_of_lex t = NULLP, int n = 0, const string& buf = "noname"): type(t), number(t), name(buf)
    {if ((n != 0) || (t == 42) || (t == 17) || (t == 47) || (t == 46)) number = n;}
    explicit Lexeme( int val, type_of_lex t = NULLP ): type(t), number(t), int_val(val)
    {}
    explicit Lexeme( double val, type_of_lex t = NULLP): type(t), number(t), bool_val(val)
    {}
    explicit Lexeme( string val, type_of_lex t = NULLP): type(t), number(t), str_val(val)
    {}
    type_of_lex get_type ( ) const
    {
        return type;
    }
    int get_number( ) const
    {
        return number;
    }

    void set_number(int number)
    //int set_number(int number)
    {
        this->number = number;
    }
    string get_name()
    {
        return name;
    }
    friend ostream& operator << (ostream &s, Lexeme l )
    {
        s << '(';
        print_type(l.type);
        if (l.type == IDENTIFIER) {s << ", " << l.number << "): " << table_of_ident[l.number] << '\n';}
        else if (l.type == LABEL) {s << ", " << l.number << "): " << table_of_label[l.number] << '\n';}
        else if (l.type == CONST_INT) { s << ", " << l.number << "): " << l.int_val << '\n';}
        else if (l.type == CONST_BOOL) { s << ", " << l.number << "): " << l.bool_val << '\n';}
        else if (l.type == CONST_STR) { s << ", " << l.number << "): " << l.str_val << '\n';}
        else if (l.type == POLIZ_ADDRESS) {s << ", " << l.number << "): " << table_of_ident[l.number] << '\n';}
        else s << ", " << l.number << ")\n";
        return s;

        // s << '(';
        // print_type(l.type);
        // if (l.type == IDENTIFIER) {s << ", " << l.number << "): " << table_of_ident[l.number] << '\n';}
        // else if (l.type == LABEL) {s << ", " << l.number << "): " << table_of_label[l.number] << '\n';}
        // else s << ", " << l.number << ")\n";
        // return s;
    }
};


//-----------------------------------------------------------------------------------------------------------



class Lex_Scanner {
    static int line;
    ifstream file;
    char c;
    int int_value;
    bool bool_value;
    string str_value;

    static int find_in_table (const string& buf, const string list[])
    {
        int i = 0;
        while ( list[i] != "" ) {
            if (buf == list[i++])
                return i;
        }
        return 0;
    }

    char gc() { file.get(c); return c;}
public:

    static int get_line() {return line;}

    static const string sep_symbols[];
    static const string service_words[];

    Lex_Scanner (const char *program)
    {
        file.open(program);
        if (!file.is_open())
        {
            throw "Can't open file!\n";
        }
    }
    ~Lex_Scanner() { file.close(); }

    Lexeme get_lex ();

};

int Lex_Scanner::line = 1;

const string Lex_Scanner:: service_words[] =
        {"program", "and", "or", "not", "true", "false", "else", "if", "int", "read", "while", "write", "for", "string", "bool", "do", "goto", ""};

const string Lex_Scanner:: sep_symbols[] =
        { ";", ",", ":", "{", "}", "(", ")", "+", "-", "*", "/",
          "=", "!=", "<", ">", "<=", ">=", "==", "%", "\"" , ""};


//---------------------------------------------------------------------------------------------------------

Lexeme Lex_Scanner::get_lex ( ) {

    enum state { START, IDENT_OR_LABEL, NUMB, RL, STR, COMMENT, ALE, NOTEQ, COMMENT_OR_DIV };
    state current_state = START;
    string buf;
    streampos old_pos;
    int d = 0, j;

    double r;

    int after_dec = 1;

    do {
        old_pos = file.tellg();
        if (file.eof()) { return Lexeme(FINAL); }
        gc();
        switch(current_state) {
            case START:
                if ( c == ' ' || c == '\t' );
                else if (c == '\n') line++;
                else if (isalpha(c)) { buf.push_back(c); current_state = IDENT_OR_LABEL; }
                else if (isdigit(c)) { d = c - '0'; current_state = NUMB; }
                else if ( c == '/' ) { current_state = COMMENT_OR_DIV;}
                else if ( c == '<' || c == '>' || c == '=') { buf.push_back(c); current_state = ALE; }
                else if ( c == '!' ) { buf.push_back(c); current_state = NOTEQ; }
                else if ( c == '\"') { current_state = STR; }
                else
                {
                    buf.push_back(c);
                    if ((j = find_in_table(buf, sep_symbols)))
                        return Lexeme((type_of_lex) (j + (int)FINAL));
                    else throw c;
                }
                break;

            case IDENT_OR_LABEL:
                if ((isalpha(c) || isdigit(c))) { buf.push_back(c);}
                else {
                    if ( c == ':')
                    {
                        j = put_label(buf, line);
                        table_of_label[j].set_declared();
                        return Lexeme(LABEL, j, buf);
                    } else {
                        file.seekg(old_pos);
                        if ((j = find_in_table(buf, service_words))) {
                            return Lexeme((type_of_lex) (j - 1));
                        } else {
                            if ((j = find_label(buf))) {return Lexeme(LABEL, j-1, buf);};
                            j = put_ident(buf);
                            return Lexeme(IDENTIFIER, j, buf);
                        }
                    }
                }
                break;

            case NUMB:

                if ( isdigit (c) ) { d = d * 10 + (c - '0'); }
                else if (c == 'b') { r = (d!=0); current_state = RL;}
                else if (isalpha(c)) { string err = "Lexical Error - Wrong identifier name!"; throw err;}
                else {
                    file.seekg(old_pos);
                    int_value = d;
                    return Lexeme( d,CONST_INT);
                }
                break;

            case RL:
                if ( isdigit (c) || isalpha(c)) {string err = "Lexical Error - Wrong identifier name!"; throw err;}
                else {
                    file.seekg(old_pos);
                    bool_value = r;
                    return Lexeme( r,CONST_BOOL);
                }
                break;

            case STR:
                if (c == '\"') { str_value = buf; return Lexeme(buf,CONST_STR); }
                else {
                    buf.push_back(c);
                }
                break;

            case ALE:
                if ( c == '=' )
                {
                    buf.push_back(c);
                    j = find_in_table( buf, sep_symbols );
                    return Lexeme((type_of_lex) (j + (int)FINAL));
                } else {
                    file.seekg(old_pos);
                    j = find_in_table (buf, sep_symbols);
                    return Lexeme((type_of_lex) ( j + (int)FINAL));
                }
                break;

            case NOTEQ:
                if ( c == '=' )
                {
                    buf.push_back(c);
                    j = find_in_table( buf, sep_symbols );
                    return Lexeme( NEQ);
                }
                else throw '!';
                break;

            case COMMENT_OR_DIV:
                if ( c == '*' )
                    current_state = COMMENT;
                else {
                    file.seekg(old_pos);
                    return Lexeme( SLASH);
                }
                break;
            case COMMENT:
                if (c == '*') if (gc() == '/') current_state = START;
                break;
        }
    } while ( true );
}

//---------------------------------------------------------------------------------------------------------

template <class T, class T_EL>
void from_st ( T & st, T_EL & i ) {
    try {
        i = st.top(); st.pop();
    }
    catch (...){
        cout << "Error in from_st";
    }
}


class Parser
{
    Lexeme curr_lex;
    Stack <type_of_lex, 100>   st_lex;

    type_of_lex l_type;
    int l_val;

    Lex_Scanner scanner;

    bool flag_for_id = true;
    int number;


    void P(); //program
    void D(); //declaration
    void D1();//declaration1
    void O();
    void O1();

    void E0();//priority0
    void E(); //priority1
    void E1();//priority2
    void T(); //
    void F();

    void gl()
    {
        try {
            curr_lex = scanner.get_lex();
            l_type = curr_lex.get_type();
            l_val = curr_lex.get_number();
        }
        catch ( char c ) {
            cout << "Unexpected symbol " << c << " found" << endl;
        }
        catch ( string s ) {
            cout << s;
        }
    }

public:

    vector <Lexeme> poliz;

    Parser(const char* program): scanner(program)
    {}

    int get_line()
    {
        return scanner.get_line();
    }

    void analyse()
    {
        gl();
        P();
       // st_lex.print();
        if (!st_lex.is_empty()) throw "Error with operands! Stack is not empty";
        cout << '\n';
        for (vector<Label>::iterator i = table_of_label.begin(); i != table_of_label.end(); i++) {
            if (!(i->get_declared())) throw "Using of non declared label!";
            for (int j = 0; j < poliz.size(); j++)
            {
                if ((poliz[j].get_type() == POLIZ_LABEL) && (poliz[j].get_name() == i->get_name()))
                    poliz[j].set_number(i->get_line());
            }
        }
        while (!(table_of_ident[table_of_ident.size() - 1].get_declare())) table_of_ident.pop_back();
        cout << '\n' << "Syntax analysis COMPLETED! " << '\n';
    }

    void check_op()
    {
        type_of_lex t1, t2, op;
        t2 = st_lex.pop();
        op = st_lex.pop();
        t1 = st_lex.pop();
        if ((t2 == STRING) && (t1 == STRING))
        {
            if (op == PLUS) st_lex.push(STRING);
            else if (op == LS || op == GE || op == TWOEQUAL || op == NEQ) st_lex.push(INT);
            else throw "Wrong operation with STRING. Only + can be used.";
        } else if ((t1 == INT || t1 == BOOL) && ((t2 == INT || t2 == BOOL))) {

            if (op == PLUS || op == MIN || op == MUL || op == SLASH || op == PERCENT) {
                if (t1 != STRING && t2 != STRING) st_lex.push(INT);
                //else st_lex.push(BOOL);
            } else if (op == LS || op == GE || op == TWOEQUAL || op == NEQ || op == GEQ || op == LEQ) st_lex.push(INT);
            else if ((op == AND || op == OR) && (t2 == t1) && (t1 != STRING)) st_lex.push(INT);
            else throw "Wrong operations with INT or BOOL";
        }
        else throw "Wrong operands combination!";
        poliz.push_back (Lexeme(op));
    }

    void check_id()
    {
        int number = curr_lex.get_number();
        if (table_of_ident[number].get_declare())
        {
            switch (table_of_ident[number].get_type_of_id()) {
                case INT_VAR: st_lex.push(INT); break;
                case STR_VAR: st_lex.push(STRING); break;
                case BOOL_VAR: st_lex.push(BOOL); break;
            }
        } else throw "variable not declared!";
    }

    void check_not () {
        if (st_lex.pop() != INT)
            throw "Using NOT with wrong type!";
        else {
            st_lex.push(INT);
            poliz.push_back(Lexeme(NOT));
        }
    }


    void eq_type()
    {
       type_of_lex sec =  st_lex.pop();
       type_of_lex first =  st_lex.pop();
       if (((first == INT) || (first == BOOL)) && (sec == INT || sec == BOOL)) {st_lex.push(first);}
       else if ((first == STRING) && (sec == STRING)) {st_lex.push(first);}
       else throw "Wrong types in assign!";
    }

    void eq_int()
    {
        if (st_lex.pop()!= INT) throw "expression is not int";
    }


};


void Parser::P()
{
    cout << "Begining of P - " << curr_lex << scanner.get_line() << '\n';
    if (l_type == PROGRAM)
    {
        gl();
        if (l_type == L_BRACKET) { gl(); D(); cout << "First after declaration - " << curr_lex << "\n"; O(); } else throw curr_lex;
    } else {
        throw curr_lex;
    }
    if (l_type != R_BRACKET) throw curr_lex;
    gl();
    cout <<"lAST lexeme - " << curr_lex << scanner.get_line() << '\n';
    if (l_type != FINAL) throw curr_lex;
    cout << "End of P - " << curr_lex << scanner.get_line() << '\n';
}

void Parser::D1()
{
    int number;
    cout << "Begining of D1 - " << curr_lex << scanner.get_line() << '\n';
    if (l_type == INT) {
        do {
            gl();
            if (l_type != IDENTIFIER) throw curr_lex;
            number = curr_lex.get_number();
            if (table_of_ident[number].get_declare()) { string err = "Variable already declared!";throw err;}
            table_of_ident[number].set_declare();
            table_of_ident[number].set_type_of_id(INT_VAR);
            gl();
            if (l_type == EQ) {
                table_of_ident[number].set_init();
                gl();
                int val = 1;
                if (l_type == MIN) {gl(); val = -1;}
                if (l_type != CONST_INT) throw curr_lex;
                table_of_ident[number].set_value(curr_lex.int_val * val);
                gl();
            }
        } while (l_type == COMMA);
        if (l_type != SEMICOLON) throw curr_lex;
    }
    else if (l_type == STRING)
    {
        do {
            gl();
            if (l_type != IDENTIFIER) throw curr_lex;
            number = curr_lex.get_number();
            if (table_of_ident[number].get_declare()) { string err = "Variable already declared!"; throw err; }
            table_of_ident[number].set_declare();
            table_of_ident[number].set_type_of_id(STR_VAR);
            gl();
            if (l_type == EQ){
                table_of_ident[number].set_init();
                gl();
                if (l_type != CONST_STR) throw curr_lex;
                table_of_ident[number].set_value(curr_lex.str_val);
                gl();
            }
        } while (l_type == COMMA);
        if (l_type != SEMICOLON) throw curr_lex;
    }
    else if (l_type == BOOL)
    {
        do {
            gl();
            if (l_type != IDENTIFIER) throw curr_lex;
            number = curr_lex.get_number();
            if (table_of_ident[number].get_declare()) { string err = "Variable already declared!"; throw err; }
            table_of_ident[number].set_declare();
            table_of_ident[number].set_type_of_id(BOOL_VAR);
            gl();
            if (l_type == EQ){
                table_of_ident[number].set_init();
                gl();
                int val = 1;
                if (l_type == MIN) {gl(); val = -1;}
                table_of_ident[number].set_value(curr_lex.bool_val * val);
                if (l_type != CONST_BOOL) throw curr_lex;
                gl();
            }
        } while (l_type == COMMA);
        if (l_type != SEMICOLON) throw curr_lex;
    }
    cout << "End of D1 - " << curr_lex << scanner.get_line() << '\n';
}


void Parser::D()
{
    cout << "Begining of D - " << curr_lex << scanner.get_line() << '\n';
    D1();
    while (l_type == SEMICOLON)
    {
        gl();
        D1();
    }
    cout << "End of D - " << curr_lex << scanner.get_line() << '\n';
}

void Parser::O()
{
    if (l_type == R_BRACKET) return;
    cout << "Begining of O - " << curr_lex << scanner.get_line() << '\n';
    O1();
    gl();

    while (l_type != R_BRACKET && l_type != FINAL)
    {
        O1();
        gl();
    }
    cout << "End of O - " << curr_lex << scanner.get_line() << '\n';
}


void Parser::O1() {
    int pl0, pl1, pl2, pl3;
    cout << "Begining of O1 - " << curr_lex << scanner.get_line() << '\n';
    flag_for_id = true;
    if (l_type == IF) {
        gl();
        if (l_type == L_C_BRACKET) {
            gl();
            E0();
            eq_int();
            pl2 = poliz.size();
            poliz.push_back ( Lexeme() );
            poliz.push_back ( Lexeme(POLIZ_FGO) );
            if (l_type != R_C_BRACKET) throw curr_lex;
        } else throw curr_lex;

        gl();
        if (l_type == L_BRACKET) {
            gl();
            O();

            pl3 = poliz.size ();
            poliz.push_back ( Lexeme() );

            poliz.push_back ( Lexeme ( POLIZ_GO ) );
            poliz[pl2] = Lexeme ( POLIZ_LABEL, poliz.size() );

            if (l_type != R_BRACKET) throw curr_lex;

        } else throw curr_lex;

        gl();

        if (l_type == ELSE) {

            gl();
            if (l_type == L_BRACKET) {
                gl();
                O();
                poliz[pl3] = Lexeme( POLIZ_LABEL, poliz.size() );
                if (l_type != R_BRACKET) throw curr_lex;
            } else throw curr_lex;
        } else throw curr_lex;


        } else if (l_type == WHILE) {
            pl0 = poliz.size ();
            gl();
            if (l_type == L_C_BRACKET) {
                gl();
                E0();
                eq_int();
                pl1 = poliz.size ();
                poliz.push_back ( Lexeme() );
                poliz.push_back ( Lexeme(POLIZ_FGO) );
                if (l_type != R_C_BRACKET) throw curr_lex;
            }
            else throw curr_lex;
            gl();
            if (l_type == L_BRACKET) {
                gl();
                O();
                poliz.push_back ( Lexeme( POLIZ_LABEL, pl0 ) );
                poliz.push_back ( Lexeme( POLIZ_GO) );
                poliz[pl1] = Lexeme( POLIZ_LABEL, poliz.size() );
                if (l_type != R_BRACKET) throw curr_lex;
            } else throw curr_lex;


        } else if(l_type == DO) {
            gl();
            if (l_type == L_BRACKET) {
                pl0 = poliz.size();
                gl();
                O();
                if (l_type != R_BRACKET) throw curr_lex;
            } else throw curr_lex;
            gl();
            if (l_type == WHILE) {
                gl();
                if (l_type == L_C_BRACKET) {
                    gl();
                    E0();
                    eq_int();
                    pl1 = poliz.size ();
                    poliz.push_back ( Lexeme() );
                    poliz.push_back ( Lexeme(POLIZ_FGO));
                    poliz.push_back ( Lexeme(POLIZ_LABEL, pl0));
                    poliz.push_back ( Lexeme(POLIZ_GO));
                    poliz[pl1] = Lexeme(POLIZ_LABEL, poliz.size());
                    if (l_type != R_C_BRACKET) throw curr_lex;
                    gl();
                } else throw curr_lex;
            } else throw curr_lex;

        } else if (l_type == READ) {
            gl();
            if (l_type == L_C_BRACKET) {
                gl();
                if (l_type == IDENTIFIER) {
                    int number = curr_lex.get_number();
                    if (!table_of_ident[number].get_declare()) throw "Variable not declared!";
                    poliz.push_back ( Lexeme( POLIZ_ADDRESS, number) );
                    gl();
                    if (l_type == R_C_BRACKET) {
                        gl();
                        poliz.push_back ( Lexeme(READ) );
                    } else throw curr_lex;
                } else throw curr_lex;
            } else throw curr_lex;


        } else if (l_type == WRITE) {
            gl();
            if (l_type == L_C_BRACKET) {
                gl();
                E0();
                st_lex.pop();
                while (l_type == COMMA) {
                    gl();
                    E0();
                    st_lex.pop();
                }
                if (l_type == R_C_BRACKET) {
                    gl();
                    poliz.push_back ( Lexeme( WRITE ) );
                } else throw curr_lex;
            }


        } else if (l_type == IDENTIFIER) {
            check_id();
            number = curr_lex.get_number();
            poliz.push_back (Lexeme( POLIZ_ADDRESS, number ) );
            gl();
            if (l_type == EQ) {
                gl();
                E0();
            } else  throw curr_lex;
            eq_type();
            poliz.push_back ( Lexeme( EQ ) );
            st_lex.pop();
            poliz.push_back(Lexeme(SEMICOLON));

        } else if (l_type == GOTO) {
            gl();
            if (l_type == LABEL) {

                poliz.push_back(Lexeme(POLIZ_LABEL, table_of_label[curr_lex.get_number()].get_line()));
                poliz.push_back(Lexeme(POLIZ_GO));
            } else if (l_type == IDENTIFIER){
                int j = put_label(curr_lex.get_name(), 0);
                poliz.push_back(Lexeme(POLIZ_LABEL, table_of_label[j].get_line(), curr_lex.get_name()));
                poliz.push_back(Lexeme(POLIZ_GO));
            } else { cout << "\nGot this - " << curr_lex; string err = "Expected Label!"; throw err;}
            gl();
        } else if (l_type == LABEL) {
            table_of_label[curr_lex.get_number()].set_line(poliz.size());
        }
    cout << "End of O1 - " << curr_lex << scanner.get_line() << '\n';
}

void Parser::E0()
{
    cout << "Beginning of E0 - " << curr_lex << scanner.get_line() << '\n';
    int i = 0;
    E();
    while (l_type == EQ)
    {
        if (!flag_for_id) throw "Trying to use associative assign not for identifier!";
        poliz.pop_back();
        poliz.push_back(Lexeme(POLIZ_ADDRESS, number));
        gl();
        E();
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        poliz.push_back(Lexeme(EQ));
        eq_type();
    }
    cout << "End of E0 - " << curr_lex << scanner.get_line() << '\n';
}

void Parser::E()
{
    cout << "Beginning of E - " << curr_lex << scanner.get_line() << '\n';
    E1();
    if (l_type == TWOEQUAL || l_type == LS || l_type == LEQ || l_type == GE || l_type == GEQ || l_type == NEQ)
    {
        flag_for_id = false;
        st_lex.push(l_type);
        gl();
        E1();
        check_op();
    }
    cout << "End of E - " << curr_lex << scanner.get_line() << '\n';
}


void Parser::E1()
{
    cout << "Beginning of E1 - " << curr_lex << scanner.get_line() << '\n';
    T();
    while (l_type == PLUS || l_type == MIN || l_type == OR || l_type == PERCENT )
    {
        flag_for_id = false;
        st_lex.push(l_type);
        gl();
        T();
        check_op();
    }
    cout << "End of E1 - " << curr_lex << scanner.get_line() << '\n';
}

void Parser::T()
{
    cout << "Begining of T - " << curr_lex << scanner.get_line() << '\n';
    F();
    while ( l_type == MUL || l_type == SLASH || l_type == AND )
    {
        flag_for_id = false;
        st_lex.push(l_type);
        gl();
        F();
        check_op();
    }
    cout << "End of T - " << curr_lex << scanner.get_line() << '\n';
}

void Parser::F()
{
    cout << "Begining of F - " << curr_lex << scanner.get_line() << '\n';
    if (l_type == MIN)
    {
        flag_for_id = false;
        gl();
        st_lex.push(INT);
        st_lex.push(MIN);
        //cout << "HELLLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO - " << curr_lex.int_val <<'\n';
        poliz.push_back(Lexeme(CONST_INT));
        F();
        check_op();
    }
    else if (l_type == IDENTIFIER)
    {
        check_id();
        number = curr_lex.get_number();
        poliz.push_back ( Lexeme ( IDENTIFIER , number) );
        gl();
    }
    else if (l_type == CONST_INT)
    {
        flag_for_id = false;
        poliz.push_back ( curr_lex );
        gl();
        st_lex.push(INT);
    }
    else if (l_type == CONST_STR)
    {
        flag_for_id = false;
        poliz.push_back ( curr_lex );
        gl();
        st_lex.push(STRING);
    }
    else if (l_type == CONST_BOOL)
    {
        flag_for_id = false;
        poliz.push_back ( curr_lex );
        gl();
        st_lex.push(BOOL);
    }
    else if (l_type == NOT)
    {
        flag_for_id = false;
        gl();
        F();
        check_not();
    }
    else if (l_type == L_C_BRACKET)
    {
        flag_for_id = false;
        gl();
        E();
        if (l_type == R_C_BRACKET)
            gl();
        else throw curr_lex;
    } else throw curr_lex;
    cout << "End of F - " << curr_lex << scanner.get_line() << '\n';
}

class Executor
{

public:
    void execute ( vector<Lexeme> & poliz );

};


void Executor::execute ( vector<Lexeme> & poliz ) {
    type_of_expression typeOfExpression = num;

    Lexeme pol_el;
    stack <int> args;
    stack <string> args_str;
    int index = 0, size = poliz.size();
    string s, l;
    int d, r, i, j;

    while ( index < size ) {

        pol_el = poliz[index];
        switch (pol_el.get_type()) {

            case CONST_INT:
                typeOfExpression = num;
                args.push( pol_el.int_val );
                break;

            case CONST_BOOL:
                typeOfExpression = num;
                args.push( pol_el.bool_val );
                break;

            case CONST_STR:
                typeOfExpression = str;
                args_str.push( pol_el.str_val );
                break;

            case IDENTIFIER:
                i = pol_el.get_number();
                if (table_of_ident[i].get_init()) {
                    switch (table_of_ident[i].get_type_of_id()) {
                        case STR_VAR:
                            typeOfExpression = str;
                            args_str.push(table_of_ident[pol_el.get_number()].get_str_value());
                            break;
                        case INT_VAR:
                            typeOfExpression = num;
                            args.push(table_of_ident[pol_el.get_number()].get_int_value());
                            break;
                        case BOOL_VAR:
                            typeOfExpression = num;
                            args.push(table_of_ident[pol_el.get_number()].get_bool_value());
                            break;
                    }
                    break;
                } else throw "Variable not initialized";

            case POLIZ_ADDRESS: case POLIZ_LABEL:
                args.push(pol_el.get_number());
                break;

            case NOT:
                from_st( args, i );
                args.push( !i );
                break;

            case OR:
                from_st( args, i );
                from_st( args, j );
                args.push ( j || i );
                break;

            case AND:
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j && i );
                break;

            case POLIZ_GO:
                from_st ( args, i );
                index = i - 1;
                break;

            case POLIZ_FGO:
                from_st ( args, i );
                from_st ( args, j );
                if ( !j ) index = i - 1;
                break;

            case WRITE:
                while (!args.empty() || !args_str.empty()) {
                    if (typeOfExpression == num) {
                        from_st(args, j);
                        cout << j << endl;
                    } else {
                        from_st(args_str, s);
                        cout << s << endl;
                    }
                }
                break;

            case READ:
                int k;
                from_st ( args, i );
                if ( table_of_ident[i].get_type_of_id() == INT_VAR ) {
                    cout << "Input INTEGER value for - " << table_of_ident[i].get_name () << endl;
                    cin >> k;
                    table_of_ident[i].set_value((int)k);
                }
                else if (table_of_ident[i].get_type_of_id() == BOOL_VAR )
                {
                    cout << "Input BOOL value for - " << table_of_ident[i].get_name () << endl;
                    cin >> j;
                    table_of_ident[i].set_value((double)j);
                }
                else {
                    cout << "Input STRING value for - " << table_of_ident[i].get_name() << endl;
                    cin >> s;
                    table_of_ident[i].set_value(s);
                }
                table_of_ident[i].set_init();
                break;

            case PLUS:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i + j);
                } else {
                    from_st(args_str, s);
                    from_st(args_str, l);
                    args_str.push(s + l);
                }
                break;

            case MUL:
                from_st ( args, i );
                from_st ( args, j );
                args.push ( i * j );
                break;

            case MIN:
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j - i );
                break;

            case SLASH:
                from_st ( args, i );
                from_st ( args, j );
                if (i) {
                    args.push ( int(j) / int(i) );
                    break;
                }
                else
                    throw "Divizion by zero";

            case PERCENT:
                from_st ( args, i );
                from_st ( args, j );
                if (i) {
                    args.push ( int(j) % int(i) );
                    break;
                }
                else
                    throw "Divizion by zero";

            case TWOEQUAL:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i == j);
                } else {
                        from_st(args_str, s);
                        from_st(args_str, l);
                        args.push(s == l);
                        typeOfExpression = num;
                }
                break;

            case LS:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i > j);
                } else {
                    from_st(args_str, s);
                    from_st(args_str, l);
                    args.push(s > l);
                    typeOfExpression = num;
                }
                break;

            case GE:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i < j);
                } else {
                    from_st(args_str, s);
                    from_st(args_str, l);
                    args.push(s < l);
                    typeOfExpression = num;
                }
                break;

            case LEQ:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i >= j);
                } else {
                    from_st(args_str, s);
                    from_st(args_str, l);
                    args.push(s >= l);
                    typeOfExpression = num;
                }
                break;

            case GEQ:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i <= j);
                } else {
                    from_st(args_str, s);
                    from_st(args_str, l);
                    args.push(s <= l);
                    typeOfExpression = num;
                }
                break;

            case NEQ:
                if (typeOfExpression == num) {
                    from_st(args, i);
                    from_st(args, j);
                    args.push(i != j);
                } else {
                    from_st(args_str, s);
                    from_st(args_str, l);
                    args.push(s != l);
                    typeOfExpression = num;
                }
                break;

            case EQ:
                if (typeOfExpression == num) {
                    from_st ( args, i );
                    from_st ( args, j );
                    if (table_of_ident[j].get_type_of_id() == BOOL_VAR) {
                        table_of_ident[(int) j].set_value((double) i);
                        args.push((int)i);
                    }
                    else {
                        table_of_ident[(int) j].set_value((int) i);
                        args.push((int)i);
                    }

                } else {
                    from_st(args_str, s);
                    from_st(args, j);
                    table_of_ident[j].set_value(s);
                    args_str.push(s);
                    typeOfExpression = str;
                }
                table_of_ident[j].set_init();
                break;

            case SEMICOLON:
                if (typeOfExpression == num) from_st(args, i);
                else from_st(args_str, s);
                break;



            
            default:
                throw "Unexpected element";
        }//end of switch
        ++index;
    };//end of while
    cout << "Finish of executing!!!" << endl;
}


class Interpretator {
    Parser   pars;
    Executor E;
public:
    explicit Interpretator ( const char* program ): pars (program) {}
    void     interpretation();
};

void Interpretator::interpretation () {
    pars.analyse();
    for (vector <Lexeme>::iterator it = pars.poliz.begin(); it != pars.poliz.end(); it++)
    {
        cout << *it << '\n';
    }
    vector <Ident> :: iterator k;
    k = table_of_ident.begin();
    while ( k != table_of_ident.end())
    {
        cout << *k << '\n';
        k++;
    }
    E.execute( pars.poliz );
    k = table_of_ident.begin();
    while ( k != table_of_ident.end())
    {
        cout << *k << '\n';
        k++;
    }
}

int main () {
    try {
        Interpretator I ( "program.txt" );
        I.interpretation ();
        return 0;
    }
    catch ( char c ) {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch ( Lexeme l ) {
        cout << "unexpected lexeme" << l << endl;
        return 1;
    }
    catch ( const char *source ) {
        cout << source << endl;
        return 1;
    }
    vector <Ident> :: iterator k;
    k = table_of_ident.begin();
    while ( k != table_of_ident.end())
    {
        cout << *k << '\n';
        k++;
    }
}
