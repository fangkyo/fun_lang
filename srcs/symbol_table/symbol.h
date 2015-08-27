#ifndef SYMBOL_TABLE_SYMBOL_H_
#define SYMBOL_TABLE_SYMBOL_H_

#include <memory>
#include <string>
#include <vector>

#include "base/check.h"
#include "symbol_table/data_type.h"
#include "symbol_table/scope.h"

namespace flang {

class SymbolHandler;

// Symbol is the entry of symbol table.
class Symbol {
 public:
  enum SymbolType {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_CLASS,
  };

  virtual ~Symbol();

  const std::string& getName() { return name_; }
  void setName(const std::string& name) { name_ = name; }

  SymbolType getSymbolType() const { return symbol_type_; }

  /**
   * @brief Execute a symbol hander.
   * @param[in] handler Point to a SymbolHandler instance.
   */
  virtual void execute(SymbolHandler* handler) = 0;

  /**
   * @brief Compare with another symbol.
   *
   * @param[in] symbol Another symbol to be compared.
   * @return Return true if equals, otherwise return false.
   */
  virtual bool equals(const Symbol& symbol_info) const;

  /**
   * @brief Get the scope binded to this symbol.
   *
   * By default this function returns nullptr, otherwise the symbol is a
   * function or class.
   *
   * @return The scope binded to the symbol.
   */
  virtual Scope* getScope() { return nullptr; }

  /**
   * @brief Get the data type of this symbol.
   */
  DataType* getDataType() const { return data_type_; }

  /**
   * @brief Set the data type of this variable.
   *
   * This class doesn't have the ownership of data type object.
   *
   * @param[in] data_type The data type of this variable.
   */
  void setDataType(DataType* data_type) {
    CHECK(data_type);
    data_type_ = data_type;
  }

 protected:
  Symbol(SymbolType symbol_type);
  std::string name_;
  SymbolType symbol_type_;
  DataType* data_type_;
};

class VariableSymbol : public Symbol {
 public:
  VariableSymbol();
  void execute(SymbolHandler* handler) override;
};

class FunctionSymbol : public Symbol {
 public:
  FunctionSymbol();
  void execute(SymbolHandler* handler) override;

  std::vector<VariableSymbol*>& getParameters() { return parameters_; }
  void addParameter(VariableSymbol* parameter);

  void setReturnType(DataType* data_type) {
    setDataType(data_type);
  }
  DataType* getReturnType() const {
    return getDataType();
  }

  Scope* getScope() override { return &scope_; }
  // void setScope(std::shared_ptr<Scope>& scope) { scope_ = scope; }

  /**
   * @brief Get the full name of function, including parameters and return type.
   * @return The full name of function.
   */
  std::string getFullname() { return ""; }

 private:
  Scope scope_;
  std::vector<VariableSymbol*> parameters_;
};

class ClassSymbol : public Symbol {
 public:
  ClassSymbol();
  void execute(SymbolHandler* handler) override;
  /**
   * @brief Get member function list.
   * @return The member function list.
   */
  const std::vector<FunctionSymbol*>& getFunctions();
  /**
   * @brief Add a member function.
   */
  void addFunction(FunctionSymbol* func_info);
  /**
   * @brief Get member variable list.
   * @return The member variable list.
   */
  const std::vector<VariableSymbol*>& getVariables();
  /**
   * @brief Add a member variable.
   */
  void addVariable(VariableSymbol* var_info);

  ClassType* getClassType() { return &class_type_; }

  Scope* getScope() override { return &scope_; }
  // void setScope(std::shared_ptr<Scope>& scope) { scope_ = scope; }

 private:
  Scope scope_;
  std::vector<FunctionSymbol*> member_funcs_;
  std::vector<VariableSymbol*> member_vars_;
  ClassType class_type_;
};

class SymbolHandler {
 public:
  virtual void handle(ClassSymbol*) {}
  virtual void handle(FunctionSymbol*) {}
  virtual void handle(VariableSymbol*) {}

 protected:
  SymbolHandler() {}
};

}  // namespace flang

#endif