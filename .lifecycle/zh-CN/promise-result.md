
## 承諾結果

### 配置

* 偵測器 ID：承諾結果
* 嚴重程度：資訊

### 描述

尋找所有 env::promise_result 的使用情況，它提供了 Promise 執行的結果。

這個偵測器有助於快速定位處理 Promise 結果的邏輯。

### 示例代碼

```rust
// https://github.com/ref-finance/ref-contracts/blob/b33c3a488b18f9cff82a3fdd53bf65d6aac09e15/ref-exchange/src/lib.rs#L434
let cross_call_result = match env::promise_result(0) {
    PromiseResult::Successful(result) => result,
    _ => env::panic(ERR124_CROSS_CALL_FAILED.as_bytes()),
};
```

在此示例中，根據其狀態（成功或不成功），處理 Promise 結果的方式會有所不同。
