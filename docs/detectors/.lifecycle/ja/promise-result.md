
## Promise の結果

### Configuration

* detector id: `promise-result`
* severity: info

### Description

`env::promise_result` の使用をすべて検索します。これは、Promise の実行結果を提供します。

この検出器は、Promise の結果を処理するロジックを迅速に特定するのに役立ちます。

### サンプルコード

```rust
// https://github.com/ref-finance/ref-contracts/blob/b33c3a488b18f9cff82a3fdd53bf65d6aac09e15/ref-exchange/src/lib.rs#L434
let cross_call_result = match env::promise_result(0) {
    PromiseResult::Successful(result) => result,
    _ => env::panic(ERR124_CROSS_CALL_FAILED.as_bytes()),
};
```

このサンプルでは、Promise の結果がその状態（成功したかどうか）に応じて処理されています。
