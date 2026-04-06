import sys
import os

def define_type(class_name, str):
    code = f"""
class {class_name} : public Expr {{
public:
    {class_name} ({str})
    : """
    str_list = str.split(", ")
    f= []
    
    for ele in str_list:
        name = ele.split(" ")[-1]
        f.append(f"{name}(std::move({name}))")
        
    code+=", ".join(f) + "{}\n\n"
    
    code += f"    std::any accept(Visitor &visitor) override {{\n"
    code += f"        return visitor.visit{class_name}Expr(*this);\n"
    code += f"    }}\n\n"
    
    
    for ele in str_list:
        code+= f"    const " + ele + ";\n"
    code+="};\n"
    return code

def define_ast(output_dir, types):
    path = os.path.join(output_dir, "Expr.h")
    file = open(path, 'w')
    
    to_write = """
#ifndef EXPR_H
#define EXPR_H
#include <memory>
#include <any>
#include \"Token.h\"
    """
    file.write(to_write)
    for t in types:
        parts = t.split(": ")
        name = parts[0].strip()
        fields = parts[1].strip()
        
        file.write("\nclass " + name + ";")
    file.write("\nclass Visitor {\npublic:\n")
    for t in types:
        parts = t.split(": ")
        name = parts[0].strip()
        fields = parts[1].strip()
        
        file.write(f"    virtual std::any visit{name}Expr({name}& expr) = 0;\n")
    file.write("    virtual ~Visitor() = default;\n};")
    sk = """
    
class Expr{
public:
    virtual ~Expr() = default;
    virtual std::any accept(Visitor &visitor) = 0;
};
"""
    
    file.write(sk)
    
    for t in types:
        parts = t.split(": ")
        name = parts[0].strip()
        fields = parts[1].strip()
        
        class_code = define_type(name, fields)
        file.write(class_code)
    
    file.write("\n#endif\n")
    file.close()
if __name__ == "__main__":
    if len(sys.argv) !=2:
        print("Error")
        sys.exit(64)
    
    output_directory = sys.argv[1]
    
    exprs = [
        "Binary   : std::unique_ptr<Expr> left, Token oper, std::unique_ptr<Expr> right",
        "Grouping : std::unique_ptr<Expr> expression",
        "Literal  : std::any value",
        "Unary    : Token oper, std::unique_ptr<Expr> right"
    ]
    define_ast(output_directory, exprs)
    print("Done!")