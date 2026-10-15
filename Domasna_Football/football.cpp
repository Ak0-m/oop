#include <iostream>

struct DOB
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

void strcpy(char *where, const char *from)
{
    while(*from)
    {
        *where = *from;
        where++;
        from++;
    }
    *where = '\0';
}

void add_dob(DOB *dob, unsigned short d, unsigned short m, unsigned short y)
{
    dob->day = d;
    dob->month = m;
    dob->year = y;
}

struct footballer
{
    char name[20];
    char surname[30];
    char club[40];
    DOB dob;
};

int main()
{
    footballer ft;
    footballer* ftp = &ft;

    strcpy(ftp->name, "David");
    strcpy(ftp->surname, "Arnaudov");
    strcpy(ftp->club, "FK Euromilk Gorno Lisiche");
    add_dob(&ftp->dob, 12, 5, 2009);

    std::cout<<ftp->name<<" "<<ftp->surname<<" born "<<ftp->dob.day<<"."<<ftp->dob.month<<"."<<ftp->dob.year<<" plays for "<<ftp->club<<"\n";
}
