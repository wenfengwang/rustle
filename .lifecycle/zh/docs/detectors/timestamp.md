
## 时间戳的依赖性

### 配置

* 检测器 ID：`timestamp`
* 严重性：信息

### 描述

时间戳的依赖可能导致被利用，因为矿工可能会操纵它。例如，在一个彩票合约中，如果使用时间戳来生成头奖，那么矿工可能会以某种方式操纵时间戳以赢得头奖。

**Rustle** 提供了这个检测器，帮助用户通过定位所有`timestamp`的使用情况来发现不正确的时间戳使用。

### 示例代码

这是一个彩票合约的示例。获胜者是通过时间戳来生成的，这意味着那些能够控制时间戳的人可以操纵结果。

```rust
impl Lottery{
    fn get_winner(&self) -> u32 {
        let current_time = env::block_timestamp();
        let winner_id = self.generate_winner(&current_time);

        winner_id
    }
}
```
