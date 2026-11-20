#include <iostream>
#include <cmath>

class Cpx
{
    float re;
    float im;

  public:
    Cpx(float r = .0f, float i = .0f) : re(r), im(i)
    {
    }

    Cpx(const Cpx &orig): re(orig.re), im(orig.im)
    {
    }
    
    ~Cpx()
    {
    }

    float getRe() const
    {
        return this->re;
    }
    float getIm() const
    {
        return this->im;
    }

    void print() const
    {
        std::cout<<this->re << ((this->im>=0)?"+":"") << this->im << "i\n";
    }
};

Cpx operator+(const Cpx &l, const Cpx &r)
{
    float re = l.getRe() + r.getRe();
    float im = l.getIm() + r.getIm();
    return Cpx(re,im);
}

Cpx operator-(const Cpx &l, const Cpx &r)
{
    float re = l.getRe() - r.getRe();
    float im = l.getIm() - r.getIm();
    return Cpx(re,im);
}

Cpx operator*(const Cpx &l, const Cpx &r)
{
    float re = l.getRe() * r.getRe() - l.getIm() * r.getIm();
    float im = l.getRe() * r.getIm() + l.getIm() * r.getRe();
    return Cpx(re,im);
}

Cpx operator/(const Cpx &l, const Cpx &r)
{
    float denom = r.getRe() * r.getRe() + r.getIm() * r.getIm();
    float re = (l.getRe() * r.getRe() + l.getIm() * r.getIm()) / denom;
    float im = (l.getIm() * r.getRe() - l.getRe() * r.getIm()) / denom;

    return Cpx(re, im);
}

float operator~(const Cpx &z)
{
    float modulus = std::sqrt(z.getRe() * z.getRe() + z.getIm() * z.getIm());
    return modulus;
}    



int main()
{
    Cpx z1(3, 2);
    Cpx z2(10, 10);
    Cpx z3 = z1 + z2;
    Cpx z4 = z3 * z1;
    Cpx z5 = z4 - z1;
    Cpx z6 = z5 / Cpx(2,2);
    float mod = ~z6;
    
    z1.print();
    z2.print();
    z3.print();
    z4.print();
    z5.print();
    z6.print();

    std::cout<<mod<<"\n";
       
  
}    
