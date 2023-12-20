
## 时间戳依赖问题

### 配置详情

* 检测器编号：时间戳
* 严重等级：信息

### 问题描述

时间戳的依赖可能导致被恶意利用，因为矿工有可能对其进行操纵。例如，在一个彩票合约中，如果使用时间戳来决定中奖号码，矿工就可能找到方法操纵时间戳以赢得大奖。

**Rustle**提供了这个检测器，旨在帮助用户通过识别出所有`timestamp`的使用场景，从而找出时间戳使用上的错误。

### 示例代码

以下是一个彩票合约的示例。中奖者是根据时间戳来确定的，这意味着如果有人能够控制时间戳，就能够操纵开奖结果。

```rust
impl Lottery{
    fn get_winner(&self) -> u32 {
        let current_time = env::block_timestamp();
        let winner_id = self.generate_winner(&current_time);

        winner_id
    }
}
```
