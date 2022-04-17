# Cコンパイラ

## Reference

[低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook)

## EBNF

* a* = aの0回以上の繰り返し
* a? = Aまたはε
* (...) = グループ化 

## 再帰下降構文解析

```
expr = mul ("+" mul | "-" mul)*
mul  = primary ("*" primary | "/" primary)*
primary = num | "(" expr ")"
```
