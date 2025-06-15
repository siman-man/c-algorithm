# CLAUDE.md

このファイルはClaude Code (claude.ai/code)がこのリポジトリで作業する際のガイダンスを提供します。

## リポジトリ概要

競技プログラミング用のC++アルゴリズムライブラリです。各アルゴリズムは独立したプログラムとして実装されており、プログラミングコンテストですぐに使用できます。

## 開発コマンド

### コンパイル
```bash
# 標準的なコンパイル
g++ -std=c++11 filename.cpp -o filename

# クイックコンパイル（a.outを生成）
g++ filename.cpp

# コンテスト用の最適化フラグ付き
g++ -O2 -std=c++11 filename.cpp
```

### テスト実行
```bash
# 入力ファイルを使用して実行
./a.out < input.in

# 手動入力で実行
./a.out
```

## コード構成

カテゴリ別に整理されています：

- **data_structure/**: BIT（Binary Indexed Tree）、Union-Find、区間クエリ
- **graph/**: ダイクストラ法、強連結成分、LCA、トポロジカルソート、2-SAT、lowlink
- **geometry/**: 凸包、円の交点、ベクトル演算
- **segment_tree/**: 各種セグメント木の実装
- **dp/**: 動的計画法のテンプレート
- **string/**: Z-algorithmと文字列ユーティリティ
- **mm/**: マラソンマッチ用テンプレート（タイマー、乱数生成、焼きなまし法、ビームサーチ）
- **math/**: 数論とその他の数学アルゴリズム
- **ルートディレクトリ**: ネットワークフロー、行列演算、二分探索の派生

## 主要ファイル

- **template.cpp**: 共通インクルードと高速I/O設定を含む基本テンプレート
- **mm/mm_template.cpp**: Xorshift乱数生成器とTimerユーティリティを含むマラソンマッチテンプレート
- **.gitignore**: *.out、*.inファイル、.ideaディレクトリを除外

## 開発パターン

1. すべての実装には直接コンパイル可能な`main()`関数を含む
2. 高速I/Oのために`std::cin.tie(0)->sync_with_stdio(0)`を使用
3. 共通のtypedef: `typedef long long ll`
4. MOD定数は通常1000000007に設定
5. 外部依存なしの自己完結型実装