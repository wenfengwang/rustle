
## 查找所有公共接口

### 配置

* 检测器ID：public-interface
* 严重级别：信息

### 描述

公共接口是指可以被其他用户调用的函数。具体而言，它们是#[near_bindgen]结构体中未使用#[private]宏修饰的公共函数。

### 示例代码

```rust
#[near_bindgen]
impl Contract {
    pub fn withdraw(&mut self, amount: U128) -> Promise {
        unimplemented!()
    }

    pub fn check_balance(&self) -> U128 {
        unimplemented!()
    }

    #[private]
    pub fn callback_withdraw(&mut self, amount: U128) {
        unimplemented!()
    }

    fn sub_balance(&mut self, amount: u128) {
        unimplemented!()
    }
}
```

在这段示例代码中，所有四个函数都是#[near_bindgen]结构体Contract的方法。但其中只有withdraw和check_balance属于公共接口。callback_withdraw虽然是公共函数，但由于使用了#[private]进行修饰，因此它是一个内部函数。sub_balance是Contract的私有函数。
