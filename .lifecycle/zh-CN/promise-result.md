
## 承诺结果

### 配置

* 检测器 ID：promise-result
* 严重程度：信息

### 描述

查找所有 env::promise_result 的使用情况，它提供了承诺执行的结果。

此检测器有助于快速定位处理承诺结果的逻辑。

### 示例代码

```rust
// https://github.com/ref-finance/ref-contracts/blob/b33c3a488b18f9cff82a3fdd53bf65d6aac09e15/ref-exchange/src/lib.rs#L434
let cross_call_result = match env::promise_result(0) {
    PromiseResult::Successful(result) => result,
    _ => env::panic(ERR124_CROSS_CALL_FAILED.as_bytes()),
};
```

在这个示例中，根据承诺的结果状态（成功或不成功）来处理承诺结果。
