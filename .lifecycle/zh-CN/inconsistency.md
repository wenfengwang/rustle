
## 符号使用不一致

### 配置项

* 检测器编号：不一致性
* 严重级别：信息

### 描述

名字相似但微妙不同的符号可能被错误使用。手动查找此类错误十分困难，但可能导致严重后果。

### 示例代码

```rust
ext::ft_transfer(
    receiver_id,
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_NFT_TRANSFER  // should use GAS_FOR_FT_TRANSFER here
)
```

在这个例子中，合约应当使用 GAS_FOR_FT_TRANSFER 而非 GAS_FOR_NFT_TRANSFER。这两个常数的数值可能有很大差异，而为 ft_transfer 分配的 Gas 可能不足。
