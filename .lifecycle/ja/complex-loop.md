
## ループ内の複雑なロジック

### Configuration

* detector id: `complex-loop`
* severity: info

### 説明

DoS問題を引き起こす可能性のある複雑なロジックを含むループを検出します。

DoS問題を避けるためには、反復回数を制限することを推奨します。

### サンプルコード

```rust
impl User {
    pub fn complex_calc(&mut self) {
        // ...
    }
}

#[near_bindgen]
impl Contract {
    pub fn register_users(&mut self, user: User) {
        self.users.push(user);
    }

    pub fn update_all_users(&mut self) {
        for user in self.users.iter_mut() {
            user.complex_calc();
        }
    }
}
```

このサンプルでは、ユーザーはストレージ料金を支払うことなく登録できるため、`users`リストは非常に長い`len()`を持つ可能性があります。

`complex_calc`関数が多くの複雑な計算を含み、多くのガスを消費する可能性があると仮定します。

`update_all_users`では、`complex_calc`関数を呼び出しながら`users`をイテレートするループがあります。これにより、全てのガスが消耗される可能性があります。

悪意のあるユーザーは、ストレージ料金を支払わずに大量のユーザーを登録することで攻撃を行うことができます。
