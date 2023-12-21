
## クロスコントラクト呼び出し

### 設定

* 検出器ID: `ext-call`
* 重大度: 情報

### 説明

すべてのクロスコントラクト呼び出しを見つけます。

この検出器は、ユーザーがすべてのクロスコントラクト呼び出しを迅速に特定し、さらに分析するために提供されています。

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

> マクロ `#[ext_contract(...)]` はRustトレイトを静的メソッドを持つモジュールに変換し、ユーザーがクロスコントラクト呼び出しを行うことを可能にします。これらの静的メソッドは、Traitによって定義された位置引数を取り、次に `receiver_id`、添付されたデポジット、ガスの量を取り、新しい `Promise` を返します。

このサンプルでは、コントラクトはクロスコントラクト呼び出し（つまり `ext_calculator::ext(calculator_account_id).sum(a, b)`）を使用して `a` と `b` の合計を取得できます。
