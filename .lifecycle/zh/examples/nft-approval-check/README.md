# 检测器示例 `nft-approval-check`

这个示例是基于[NEAR合同标准](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs)的实现。然而，新增了一个名为[`internal_transfer_unsafe`](src/lib.rs#L256)的新函数。在这个函数中，移除了对`approval_id`的检查，这是不正确的。

接口`nft_transfer`将调用这个新的不安全的`internal_transfer_unsafe`，而`nft_transfer_call`仍将使用安全的`internal_transfer`。因此，**Rustle**会将`nft_transfer`标记为不安全的。