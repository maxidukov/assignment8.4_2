#ifndef ALL_CLASSES_H
#define ALL_CLASSES_H

#include <fstream>
#include <memory> //FOR std::unique_ptr

class PrintableText;
class PrintableHTML;
class PrintableJSON;


class Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };
protected:
    Format format_;
    std::string data_;

public:

    // virtual ~Printable();
    Printable(std::string data, Format format): data_(data), format_(format) {}

    virtual std::string print() const { return data_; }; //NO LONGER PURE VIRTUAL
    void saveTo(std::ofstream &file){
        file << print() << std::endl;
    }
    std::unique_ptr<Printable> MakePrintable(); //DEFINED DOWN BELOW, BECAUSE ALL DERIVED TYPES NEEDED
};

class PrintableText : public Printable{
    Format format_;
    std::string data_;
public:
    PrintableText(std::string data): Printable(data,Printable::Format::kText), data_(data){}
    std::string print() const override{
        return data_;
    }
};

class PrintableHTML : public Printable{
    Format format_;
    std::string data_;
public:
    PrintableHTML(std::string data): Printable(data,Printable::Format::kHTML), data_(data){}
    std::string print() const override{
        return "<html>" + data_ + "<html/>";
    }
};

class PrintableJSON : public Printable{
    Format format_;
    std::string data_;
public:
    PrintableJSON(std::string data): Printable(data,Printable::Format::kJSON), data_(data){}
    std::string print() const override{
        return "{ \"data\": \"" + data_ + "\"}";
    }
};

std::unique_ptr<Printable>Printable::MakePrintable(){
    switch(format_){
    case Printable::Format::kText: return std::unique_ptr<Printable>(new PrintableText(data_));break;
    case Printable::Format::kHTML: return std::make_unique<PrintableHTML>(data_);break;
    case Printable::Format::kJSON: return std::make_unique<PrintableJSON>(data_);break;
    default: return std::make_unique<PrintableText>(data_); break;
    }
}


#endif // ALL_CLASSES_H

