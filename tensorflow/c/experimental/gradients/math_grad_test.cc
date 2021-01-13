/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "tensorflow/c/experimental/gradients/math_grad.h"

#include "tensorflow/c/eager/c_api_test_util.h"
#include "tensorflow/c/eager/c_api_unified_experimental_internal.h"
#include "tensorflow/c/eager/unified_api_testutil.h"
#include "tensorflow/c/experimental/gradients/grad_test_helper.h"
#include "tensorflow/c/experimental/gradients/tape/tape_context.h"
#include "tensorflow/c/experimental/ops/math_ops.h"
#include "tensorflow/c/tf_status_helper.h"
#include "tensorflow/core/platform/test.h"

namespace tensorflow {
namespace gradients {
namespace internal {
namespace {

using tensorflow::TF_StatusPtr;

Status AddModel(AbstractContext* ctx,
                absl::Span<AbstractTensorHandle* const> inputs,
                absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Add(ctx, inputs, outputs, "Add");
}

Status AddGradModel(AbstractContext* ctx,
                    absl::Span<AbstractTensorHandle* const> inputs,
                    absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("AddV2", AddRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  tape.Watch(inputs[1]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Add(tape_ctx.get(), inputs,
                              absl::MakeSpan(temp_outputs), "AddGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status ExpModel(AbstractContext* ctx,
                absl::Span<AbstractTensorHandle* const> inputs,
                absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Exp(ctx, inputs, outputs, "Exp");
}

Status ExpGradModel(AbstractContext* ctx,
                    absl::Span<AbstractTensorHandle* const> inputs,
                    absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("Exp", ExpRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Exp(tape_ctx.get(), inputs,
                              absl::MakeSpan(temp_outputs), "ExpGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status SqrtModel(AbstractContext* ctx,
                 absl::Span<AbstractTensorHandle* const> inputs,
                 absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Sqrt(ctx, inputs, outputs, "Sqrt");
}

Status SqrtGradModel(AbstractContext* ctx,
                     absl::Span<AbstractTensorHandle* const> inputs,
                     absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("Sqrt", SqrtRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Sqrt(tape_ctx.get(), inputs,
                               absl::MakeSpan(temp_outputs), "SqrtGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status NegModel(AbstractContext* ctx,
                absl::Span<AbstractTensorHandle* const> inputs,
                absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Neg(ctx, inputs, outputs, "Neg");
}

Status NegGradModel(AbstractContext* ctx,
                    absl::Span<AbstractTensorHandle* const> inputs,
                    absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("Neg", NegRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Neg(tape_ctx.get(), inputs,
                              absl::MakeSpan(temp_outputs), "NegGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status SubModel(AbstractContext* ctx,
                absl::Span<AbstractTensorHandle* const> inputs,
                absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Sub(ctx, inputs, outputs, "Sub");
}

Status SubGradModel(AbstractContext* ctx,
                    absl::Span<AbstractTensorHandle* const> inputs,
                    absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("Sub", SubRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  tape.Watch(inputs[1]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Sub(tape_ctx.get(), inputs,
                              absl::MakeSpan(temp_outputs), "SubGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status MulModel(AbstractContext* ctx,
                absl::Span<AbstractTensorHandle* const> inputs,
                absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Mul(ctx, inputs, outputs, "Mul");
}

Status MulGradModel(AbstractContext* ctx,
                    absl::Span<AbstractTensorHandle* const> inputs,
                    absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("Mul", MulRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  tape.Watch(inputs[1]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Mul(tape_ctx.get(), inputs,
                              absl::MakeSpan(temp_outputs), "MulGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status Log1pModel(AbstractContext* ctx,
                  absl::Span<AbstractTensorHandle* const> inputs,
                  absl::Span<AbstractTensorHandle*> outputs) {
  return ops::Log1p(ctx, inputs, outputs, "Log1p");
}

Status Log1pGradModel(AbstractContext* ctx,
                      absl::Span<AbstractTensorHandle* const> inputs,
                      absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("Log1p", Log1pRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::Log1p(tape_ctx.get(), inputs,
                                absl::MakeSpan(temp_outputs), "Log1pGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

Status DivNoNanModel(AbstractContext* ctx,
                     absl::Span<AbstractTensorHandle* const> inputs,
                     absl::Span<AbstractTensorHandle*> outputs) {
  return ops::DivNoNan(ctx, inputs, outputs, "DivNoNan");
}

Status DivNoNanGradModel(AbstractContext* ctx,
                         absl::Span<AbstractTensorHandle* const> inputs,
                         absl::Span<AbstractTensorHandle*> outputs) {
  GradientRegistry registry;
  TF_RETURN_IF_ERROR(registry.Register("DivNoNan", DivNoNanRegisterer));

  Tape tape(/*persistent=*/false);
  tape.Watch(inputs[0]);
  tape.Watch(inputs[1]);
  std::vector<AbstractTensorHandle*> temp_outputs(1);
  AbstractContextPtr tape_ctx(new TapeContext(ctx, &tape, registry));
  TF_RETURN_IF_ERROR(ops::DivNoNan(
      tape_ctx.get(), inputs, absl::MakeSpan(temp_outputs), "DivNoNanGrad"));

  TF_RETURN_IF_ERROR(tape.ComputeGradient(ctx, /*targets=*/temp_outputs,
                                          /*sources=*/inputs,
                                          /*output_gradients=*/{}, outputs));
  for (auto temp_output : temp_outputs) {
    temp_output->Unref();
  }
  return Status::OK();
}

class CppGradients
    : public ::testing::TestWithParam<std::tuple<const char*, bool, bool>> {
 protected:
  void SetUp() override {
    TF_StatusPtr status(TF_NewStatus());
    TF_SetTracingImplementation(std::get<0>(GetParam()), status.get());
    Status s = StatusFromTF_Status(status.get());
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();

    {
      AbstractContext* ctx_raw = nullptr;
      Status s =
          BuildImmediateExecutionContext(std::get<1>(GetParam()), &ctx_raw);
      ASSERT_EQ(errors::OK, s.code()) << s.error_message();
      ctx_.reset(ctx_raw);
    }
  }

  AbstractContextPtr ctx_;

 public:
  bool UseMlir() const { return strcmp(std::get<0>(GetParam()), "mlir") == 0; }
  bool UseFunction() const { return std::get<2>(GetParam()); }
};

TEST_P(CppGradients, TestAddGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  AbstractTensorHandlePtr y;
  {
    AbstractTensorHandle* y_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &y_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    y.reset(y_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      AddModel, AddGradModel, ctx_.get(), {x.get(), y.get()}, UseFunction()));
}

TEST_P(CppGradients, TestExpGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      ExpModel, ExpGradModel, ctx_.get(), {x.get()}, UseFunction()));
}

TEST_P(CppGradients, TestSqrtGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      SqrtModel, SqrtGradModel, ctx_.get(), {x.get()}, UseFunction()));
}

TEST_P(CppGradients, TestNegGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      NegModel, NegGradModel, ctx_.get(), {x.get()}, UseFunction()));
}

TEST_P(CppGradients, TestSubGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  AbstractTensorHandlePtr y;
  {
    AbstractTensorHandle* y_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &y_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    y.reset(y_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      SubModel, SubGradModel, ctx_.get(), {x.get(), y.get()}, UseFunction()));
}

TEST_P(CppGradients, TestMulGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  AbstractTensorHandlePtr y;
  {
    AbstractTensorHandle* y_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &y_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    y.reset(y_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      MulModel, MulGradModel, ctx_.get(), {x.get(), y.get()}, UseFunction()));
}

TEST_P(CppGradients, TestLog1pGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      Log1pModel, Log1pGradModel, ctx_.get(), {x.get()}, UseFunction()));
}

TEST_P(CppGradients, TestDivNoNanGrad) {
  AbstractTensorHandlePtr x;
  {
    AbstractTensorHandle* x_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &x_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    x.reset(x_raw);
  }

  AbstractTensorHandlePtr y;
  {
    AbstractTensorHandle* y_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 2.0f, &y_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    y.reset(y_raw);
  }

  ASSERT_NO_FATAL_FAILURE(CompareNumericalAndAutodiffGradients(
      DivNoNanModel, DivNoNanGradModel, ctx_.get(), {x.get(), y.get()},
      UseFunction()));

  // `DivNoNanGradModel` should return {`0`, `0`} when the denominator is `0`.
  AbstractTensorHandlePtr z;
  {
    AbstractTensorHandle* z_raw = nullptr;
    Status s = TestScalarTensorHandle(ctx_.get(), 0.0f, &z_raw);
    ASSERT_EQ(errors::OK, s.code()) << s.error_message();
    z.reset(z_raw);
  }
  std::vector<AbstractTensorHandle*> outputs(2);
  auto s = RunModel(DivNoNanGradModel, ctx_.get(), {x.get(), z.get()},
                    absl::MakeSpan(outputs), UseFunction());
  ASSERT_EQ(errors::OK, s.code()) << s.error_message();
  ASSERT_NO_FATAL_FAILURE(CheckTensorValue(outputs[0], {0.0f}, /*dims*/ {},
                                           /*abs_error*/ 0));
  ASSERT_NO_FATAL_FAILURE(CheckTensorValue(outputs[1], {0.0f}, /*dims*/ {},
                                           /*abs_error*/ 0));
  outputs[0]->Unref();
  outputs[1]->Unref();
}

#ifdef PLATFORM_GOOGLE
INSTANTIATE_TEST_SUITE_P(
    UnifiedCAPI, CppGradients,
    ::testing::Combine(::testing::Values("graphdef", "mlir"),
                       /*tfrt*/ ::testing::Values(false),
                       /*use_function*/ ::testing::Values(true, false)));
#else
INSTANTIATE_TEST_SUITE_P(
    UnifiedCAPI, CppGradients,
    ::testing::Combine(::testing::Values("graphdef", "mlir"),
                       /*tfrt*/ ::testing::Values(false),
                       /*use_function*/ ::testing::Values(true, false)));
#endif
}  // namespace
}  // namespace internal
}  // namespace gradients
}  // namespace tensorflow
