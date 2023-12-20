
## 符号使用不一致

### 配置项

* 检测器编号：不一致性
* 严重级别：信息

### 描述

名称相似但略有差异的符号可能被错误使用。这种错误手工发现很困难，但可能导致重大问题。

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

在这个例子中，合约应当使用 GAS_FOR_FT_TRANSFER 而非 GAS_FOR_NFT_TRANSFER。这两个常数的值可能有很大差异，而且用于 ft_transfer 的 Gas 可能不足。
