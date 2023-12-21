
## Promise の結果

### 設定

* detector id: `promise-result`
* severity: info

### 説明

`env::promise_result` の使用をすべて見つけ出し、これによりPromiseの実行結果が提供されます。

この検出器は、Promiseの結果を処理するロジックを迅速に特定するのに役立ちます。

### サンプルコード

```rust
// https://github.com/ref-finance/ref-contracts/blob/b33c3a488b18f9cff82a3fdd53bf65d6aac09e15/ref-exchange/src/lib.rs#L434
let cross_call_result = match env::promise_result(0) {
    PromiseResult::Successful(result) => result,
    _ => env::panic(ERR124_CROSS_CALL_FAILED.as_bytes()),
};
```

このサンプルでは、Promise の結果はその状態（成功したかどうか）に応じて処理されます。
