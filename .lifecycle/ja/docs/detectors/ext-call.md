
## クロスコントラクト呼び出し

### 設定

* 検出器ID: `ext-call`
* 重大度: 情報

### 説明

すべてのクロスコントラクト呼び出しを見つけます。

この検出器は、ユーザーがすべてのクロスコントラクト呼び出しを迅速に特定し、さらに分析するための支援を提供します。

### サンプルコード

```rust
// https://docs.near.org/sdk/rust/cross-contract/callbacks#calculator-example
#[ext_contract(ext_calculator)]
trait Calculator {
    fn sum(&self, a: U128, b: U128) -> U128;
}

#[near_bindgen]
impl Contract {
    pub fn sum_a_b(&mut self, a: U128, b: U128) -> Promise {
        let calculator_account_id: AccountId = "calc.near".parse().unwrap();
        ext_calculator::ext(calculator_account_id).sum(a, b)  // リモートでsum(a, b)を実行
    }
}
```

> マクロ `#[ext_contract(...)]` は、Rustのトレイトを静的メソッドを持つモジュールに変換します。これにより、ユーザーはクロスコントラクト呼び出しを行うことができます。これらの静的メソッドは、トレイトによって定義された位置引数を取り、`receiver_id`、添付されたデポジット、およびガスの量を指定し、新しい `Promise` を返します。

このサンプルでは、コントラクトはクロスコントラクト呼び出し（つまり `ext_calculator::ext(calculator_account_id).sum(a, b)`）を使用して `a` と `b` の合計を取得できます。
