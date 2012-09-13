/* JFlex example: part of Java language lexer specification 
	Alex Wellock*/

import java_cup.runtime.*;

/**
 * This class is a simple example lexer.
 */
%%

%public
%class Lexer
%extends Sym

%unicode

%debug
%line
%column
%cupsym Sym
%cup

%{
  int ANY = 0;
  StringBuffer string = new StringBuffer();
  Sym sym;

  private Symbol symbol(int type) {
    return new Symbol(type, yyline, yycolumn);
  }
  private Symbol symbol(int type, Object value) {
    return new Symbol(type, yyline, yycolumn, value);
  }
%}

%eof{
  /* your code goes here */
%eof}

LineTerminator = \r|\n|\r\n
InputCharacter = [^\r\n]
WhiteSpace     = {LineTerminator} | [ \t\f]

EndOfLineComment     = "//" {InputCharacter}* {LineTerminator}

Identifier = [:jletter:] [:jletterdigit:]*

DecIntegerLiteral = 0 | [1-9][0-9]*
HexIntegerLiteral = 0[xX][0-9a-fA-F]+|{DecIntegerLiteral}
DoubleLiteral = {DecIntegerLiteral}+\.{DecIntegerLiteral}*([eE][-+]?{DecIntegerLiteral}+)?
%state STRING
%state NESTED_COMMENT

%%

/* keywords */
<YYINITIAL> "void"				{ return symbol(sym.VOID);	}
<YYINITIAL> "int"				{ return symbol(sym.INT);	}
<YYINITIAL> "double"			{ return symbol(sym.DOUBLE);}
<YYINITIAL> "bool"				{ return symbol(sym.BOOL);	}
<YYINITIAL> "string"			{ return symbol(sym.STRING);}
<YYINITIAL> "class"             { return symbol(sym.CLASS); }
<YYINITIAL> "interface"			{ return symbol(sym.INTERFACE);}
<YYINITIAL> "null"				{ return symbol(sym.NULL);	}
<YYINITIAL> "extends"			{ return symbol(sym.EXTENDS);}
<YYINITIAL> "implements"		{ return symbol(sym.IMPLEMENTS);}
<YYINITIAL> "for"				{ return symbol(sym.FOR);	}
<YYINITIAL> "while"				{ return symbol(sym.WHILE);	}
<YYINITIAL> "if"				{ return symbol(sym.IF);	}
<YYINITIAL> "else"				{ return symbol(sym.ELSE);	}
<YYINITIAL> "return"			{ return symbol(sym.RETURN);}
<YYINITIAL> "break"				{ return symbol(sym.BREAK);	}
<YYINITIAL> "new"				{ return symbol(sym.NEW);	}
<YYINITIAL> "NewArray"			{ return symbol(sym.NEWARRAY);}
<YYINITIAL> "Print"				{ return symbol(sym.PRINT);	}
<YYINITIAL> "ReadInteger"		{ return symbol(sym.READINTEGER);}
<YYINITIAL> "ReadLine"			{ return symbol(sym.READLINE);}
<YYINITIAL> "true"				{ return symbol(sym.BOOL, yytext()); }

<YYINITIAL> {
  /* identifiers */ 
  {Identifier}                   { 	string.setLength(0);
  									string.append(yytext());
  									return symbol(sym.IDENTIFIER, string.toString()); }
 
  /* literals */
  {DoubleLiteral}				 { return symbol(sym.DOUBLE_LITERAL); }
  {DecIntegerLiteral}            { return symbol(sym.INTEGER_LITERAL); }
  {HexIntegerLiteral}			 { return symbol(sym.INTEGER_LITERAL); }
  \"                             { string.setLength(0); yybegin(STRING); }

  /* operators */
  "+"							 { return symbol(sym.PLUS); }
  "-"							 { return symbol(sym.MINUS); }
  "*"							 { return symbol(sym.MULT); }
  "/"							 { return symbol(sym.DIV); }
  "%"							 { return symbol(sym.MOD); }
  "<" 							 { return symbol(sym.LESS); }
  ">"							 { return symbol(sym.GREAT); }
  "<="							 { return symbol(sym.LESSEQ); }
  ">="							 { return symbol(sym.GREATEQ); }
  "=="							 { return symbol(sym.EQEQ); }
  "="                            { return symbol(sym.EQ); }
  "!="							 { return symbol(sym.NOTEQ); }
  "&&"							 { return symbol(sym.AND); }
  "||"							 { return symbol(sym.OR); }
  "!"							 { return symbol(sym.NOT); }
  ";"							 { return symbol(sym.SEMICOLON); }
  ","							 { return symbol(sym.COM); }
  "."							 { return symbol(sym.PER); }
  "[]"							 { return symbol(sym.DIMS); }
  "["							 { return symbol(LBRAC); }
  "]"							 { return symbol(RBAC); }
  "("							 { return symbol(LPREN); }
  ")"							 { return symbol(RPREN); }
  "{"							 { return symbol(LCBRAC); }
  "}"							 { return symbol(RCBRAC); }
  

  /* comments */
  {EndOfLineComment}             { /* ignore comments*/ }
  
  "/*"                           { yybegin(NESTED_COMMENT); }
 
  /* whitespace */
  {WhiteSpace}                   { /* ignore whitespace*/ }
}

<STRING> {
  \"                             { yybegin(YYINITIAL); 
                                   return symbol(sym.STRING_LITERAL, 
                                   string.toString()); }
  [^\n\r\"\\]+                   { string.append( yytext() ); }
  \\t                            { string.append('\t'); }
  \\n                            { string.append('\n'); }

  \\r                            { string.append('\r'); }
  \\\"                           { string.append('\"'); }
  \\                             { string.append('\\'); }
}
<NESTED_COMMENT> {
  "*/"                           { yybegin(YYINITIAL); }
  [^*/]+                   		 {}
  [*]+							 {}
  [/]+							 {}
}
	

/* error fallback */
<YYINITIAL>.|\n                  { throw new Error("Illegal character <"+ yytext()+">"); }
