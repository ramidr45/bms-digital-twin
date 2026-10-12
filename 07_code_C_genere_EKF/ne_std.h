#ifndef __ne_std_h__
#define __ne_std_h__
#include "stddef.h"
#include "string.h"
#include "pm_inline.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct SscArraySizeTag{size_t numElements;char const*encodedDimensions
;}SscArraySize;PMF_DEPLOY_STATIC void ssc_array_size_set_scalar(SscArraySize*
size){SscArraySize const x={1,"1x1"};memcpy(size,&x,sizeof(SscArraySize));}
PMF_DEPLOY_STATIC SscArraySize ssc_make_scalar_array_size(void){SscArraySize
out;ssc_array_size_set_scalar(&out);return out;}PMF_DEPLOY_STATIC size_t
ssc_array_size_num_elements(SscArraySize const*size){return size->numElements;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "pm_std.h"
#include "pm_std.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct NeSystemInputTag{PmIntVector mQ;PmIntVector mM;PmRealVector mT;
PmRealVector mU;PmRealVector mV;PmRealVector mX;PmRealVector mD;PmIntVector mE
;PmRealVector mCR;PmIntVector mCI;}NeSystemInput;typedef enum
NeSystemInputIdTag{NE_INVALID_SYSTEM_INPUT_ID= -1,NE_SYSTEM_INPUT_ID_Q,
NE_SYSTEM_INPUT_ID_M,NE_SYSTEM_INPUT_ID_T,NE_SYSTEM_INPUT_ID_U,
NE_SYSTEM_INPUT_ID_V,NE_SYSTEM_INPUT_ID_X,NE_SYSTEM_INPUT_ID_D,
NE_SYSTEM_INPUT_ID_E,NE_SYSTEM_INPUT_ID_CR,NE_SYSTEM_INPUT_ID_CI,
NE_NUM_SYSTEM_INPUT_ID}NeSystemInputId;typedef struct NeSystemInputSizesTag{
size_t mSizes[NE_NUM_SYSTEM_INPUT_ID];}NeSystemInputSizes;NeSystemInputSizes
neu_get_empty_system_input_sizes(void);NeSystemInputSizes
neu_get_system_input_sizes(const NeSystemInput*in);NeSystemInput*
neu_create_system_input(NeSystemInputSizes sizes,PmAllocator*allocatorPtr);
void neu_destroy_system_input(NeSystemInput*sysInputPtr,PmAllocator*
allocatorPtr);void neu_si_equals_si(const NeSystemInput*destPtr,const
NeSystemInput*srcPtr);NeSystemInput*neu_copy_si(const NeSystemInput*in,
PmAllocator*al);boolean_T neu_si_equalequals_si(const NeSystemInput*destPtr,
const NeSystemInput*srcPtr);boolean_T neu_sis_equalequals_sis(const
NeSystemInputSizes left,const NeSystemInputSizes right);typedef struct
NeDynamicSystemInputTag{PmIntVector mQ;PmIntVector mM;PmRealVector mT;
PmRealVector mU;PmRealVector mV;PmRealVector mX;PmRealVector mD;PmIntVector mE
;PmRealVector mCR;PmIntVector mCI;PmRealVector mW;PmRealVector mS;PmIntVector
mP_L;PmIntVector mP_I;PmIntVector mP_J;PmRealVector mP_R;PmIntVector mDP_L;
PmIntVector mDP_I;PmIntVector mDP_J;PmRealVector mDP_R;}NeDynamicSystemInput;
typedef enum NeDynamicSystemInputIdTag{NE_INVALID_DYNAMIC_SYSTEM_INPUT_ID= -1,
NE_DYNAMIC_SYSTEM_INPUT_ID_Q,NE_DYNAMIC_SYSTEM_INPUT_ID_M,
NE_DYNAMIC_SYSTEM_INPUT_ID_T,NE_DYNAMIC_SYSTEM_INPUT_ID_U,
NE_DYNAMIC_SYSTEM_INPUT_ID_V,NE_DYNAMIC_SYSTEM_INPUT_ID_X,
NE_DYNAMIC_SYSTEM_INPUT_ID_D,NE_DYNAMIC_SYSTEM_INPUT_ID_E,
NE_DYNAMIC_SYSTEM_INPUT_ID_CR,NE_DYNAMIC_SYSTEM_INPUT_ID_CI,
NE_DYNAMIC_SYSTEM_INPUT_ID_W,NE_DYNAMIC_SYSTEM_INPUT_ID_S,
NE_DYNAMIC_SYSTEM_INPUT_ID_P_L,NE_DYNAMIC_SYSTEM_INPUT_ID_P_I,
NE_DYNAMIC_SYSTEM_INPUT_ID_P_J,NE_DYNAMIC_SYSTEM_INPUT_ID_P_R,
NE_DYNAMIC_SYSTEM_INPUT_ID_DP_L,NE_DYNAMIC_SYSTEM_INPUT_ID_DP_I,
NE_DYNAMIC_SYSTEM_INPUT_ID_DP_J,NE_DYNAMIC_SYSTEM_INPUT_ID_DP_R,
NE_NUM_DYNAMIC_SYSTEM_INPUT_ID}NeDynamicSystemInputId;typedef struct
NeDynamicSystemInputSizesTag{size_t mSizes[NE_NUM_DYNAMIC_SYSTEM_INPUT_ID];}
NeDynamicSystemInputSizes;NeDynamicSystemInputSizes
neu_get_empty_dynamic_system_input_sizes(void);NeDynamicSystemInputSizes
neu_get_dynamic_system_input_sizes(const NeDynamicSystemInput*in);
NeDynamicSystemInput*neu_create_dynamic_system_input(NeDynamicSystemInputSizes
sizes,PmAllocator*allocatorPtr);void neu_destroy_dynamic_system_input(
NeDynamicSystemInput*sysInputPtr,PmAllocator*allocatorPtr);void
neu_dsi_equals_dsi(const NeDynamicSystemInput*destPtr,const
NeDynamicSystemInput*srcPtr);NeDynamicSystemInput*neu_copy_dsi(const
NeDynamicSystemInput*in,PmAllocator*al);boolean_T neu_dsi_equalequals_dsi(
const NeDynamicSystemInput*destPtr,const NeDynamicSystemInput*srcPtr);
boolean_T neu_dsis_equalequals_dsis(const NeDynamicSystemInputSizes left,const
NeDynamicSystemInputSizes right);typedef enum NeEquationDomainTag{
NE_EQUATION_DOMAIN_INVALID= -1,NE_EQUATION_DOMAIN_TIME,
NE_EQUATION_DOMAIN_FREQUENCY_REAL,NE_EQUATION_DOMAIN_FREQUENCY_IMAG,
NE_EQUATION_DOMAIN_COMPLEX,NE_EQUATION_DOMAIN_DELAY,NE_EQUATION_DOMAIN_NUM}
NeEquationDomain;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "pm_std.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef uint32_T NeChecksum[4];typedef enum NeVariabilityTypeTag{
NE_INVALID_VARIABILITY= -1,NE_CONSTANT_VARIABILITY,NE_PARAMETRIC_VARIABILITY,
NE_MODAL_VARIABILITY,NE_FULL_VARIABILITY}NeVariabilityType;typedef enum
NeInitModeTag{NE_INIT_MODE_INVALID= -1,NE_INIT_MODE_DEFAULT,NE_INIT_MODE_NONE,
NE_INIT_MODE_OPTIONAL,NE_INIT_MODE_MANDATORY,NE_INIT_MODE_NUM}NeInitMode;
typedef enum NeNominalSourceTag{NE_NOMINAL_SOURCE_INVALID= -1,
NE_NOMINAL_SOURCE_NONE,NE_NOMINAL_SOURCE_MODEL,NE_NOMINAL_SOURCE_BLOCK,
NE_NOMINAL_SOURCE_DERIVED,NE_NOMINAL_SOURCE_FIXED,NE_NOMINAL_SOURCE_NUM}
NeNominalSource;typedef enum NeFreqTimeTypeTag{NE_FREQTIME_TYPE_INVALID= -1,
NE_FREQTIME_TYPE_TIME,NE_FREQTIME_TYPE_FREQUENCY,NE_FREQTIME_TYPE_PARTFREQ,
NE_FREQTIME_TYPE_NUM}NeFreqTimeType;typedef unsigned int NeEquationFlag;
typedef unsigned int NeCERFlag;typedef unsigned int NeICRFlag;typedef unsigned
int NeVariableFlag;typedef struct NeEquationDataTag{const char*mFullPath;
size_t mIndex;NeEquationFlag mFlags;NeEquationDomain mDomain;const char*
mObject;size_t mNumRanges;size_t mStart;boolean_T mIsSwitchedLinear;real_T
mScale;const char*mUnit;}NeEquationData;enum{NE_NODAL_EQ_FLAG=1<<0,
NE_SIGNAL_EQ_FLAG=1<<1,NE_BRANCH_EQ_FLAG=1<<2,NE_GENERAL_EQ_FLAG=1<<3,
NE_TIME_EQ_FLAG=1<<4,NE_THROUGH_EQ_FLAG=1<<5,NE_INTEG_EQ_FLAG=1<<6,
NE_DIFFOFFSET_EQ_FLAG=1<<7,NE_DISCTIME_EQ_FLAG=1<<8,NE_NO_EQ_FLAGS=0};typedef
struct NeCERDataTag{const char*mFullPath;size_t mIndex;NeCERFlag mFlags;const
char*mObject;size_t mNumRanges;size_t mStart;boolean_T mIsLinear;}NeCERData;
enum{NE_RESERVED_FOR_FUTURE_USE_CER_FLAG=1<<0,NE_NO_CER_FLAGS=0};typedef struct
NeICRDataTag{const char*mFullPath;size_t mIndex;NeICRFlag mFlags;const char*
mObject;size_t mNumRanges;size_t mStart;}NeICRData;enum{NE_INITIAL_ICR_FLAG=1
<<0,NE_NO_ICR_FLAGS=0};typedef struct NeVariableDataTag{const char*mFullPath;
size_t mIndex;NeVariableFlag mFlags;const char*mObject;real_T mScale;const char
*mUnit;real_T mICValue;boolean_T mIsDifferential;boolean_T mHasInitialRange;
SscArraySize mSize;NeInitMode mInitMode;const char*mDescription;}
NeVariableData;enum{NE_NODAL_VAR_FLAG=1<<0,NE_OUTPUT_VAR_FLAG=1<<1,
NE_INPUT_VAR_FLAG=1<<2,NE_SIGNAL_VAR_FLAG=1<<3,NE_TIME_VAR_FLAG=1<<4,
NE_INTEG_VAR_FLAG=1<<5,NE_NO_VAR_FLAGS=0};typedef struct NeObservableDataTag{
const char*mFullPath;const char*mObject;SscArraySize mSize;const char*mUnit;
real_T mNominalValue;const char*mNominalUnit;NeNominalSource mNominalSource;
NeInitMode mInitMode;boolean_T mIsDetermined;boolean_T mIsDifferential;
NeFreqTimeType mFreqTimeType;boolean_T mIsExternal;boolean_T mIsVariable;const
char*mDescription;}NeObservableData;typedef struct NeModeDataTag{const char*
mFullPath;size_t mIndex;const char*mObject;int32_T mICValue;SscArraySize mSize
;const char*mDescription;}NeModeData;typedef enum NeRangeTypeIdTag{
NE_RANGE_TYPE_INVALID= -1,NE_RANGE_TYPE_NORMAL,NE_RANGE_TYPE_PROTECTED,
NE_RANGE_TYPE_NA,NE_RANGE_TYPE_NUM}NeRangeTypeId;typedef struct NeRangeTag{
const char*mClassName;size_t mBeginLine;size_t mBeginColumn;size_t mEndLine;
size_t mEndColumn;NeRangeTypeId mType;}NeRange;typedef enum NeZcTypeTag{
NE_ZC_TYPE_INVALID= -1,NE_ZC_TYPE_TRUE,NE_ZC_TYPE_FALSE,NE_ZC_TYPE_EITHER,
NE_ZC_TYPE_NUM}NeZcType;typedef struct NeZCDataTag{const char*mObject;size_t
mNumRanges;size_t mStart;const char*mPath;const char*mDescriptor;NeZcType mType
;}NeZCData;typedef struct NeAssertDataTag{const char*mObject;size_t mNumRanges
;size_t mStart;const char*mPath;const char*mDescriptor;boolean_T mIsWarn;const
char*mMessage;const char*mMessageID;}NeAssertData;typedef struct
NeParameterDataTag{const char*mFullPath;const char*mObject;const char*
mDescription;size_t mIndex;size_t mM;boolean_T mIsTop;}NeParameterData;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "pm_inline.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct SscIoInfoTag SscIoInfo;typedef enum SscIoTypeTag{
UNKNOWN_IO_TYPE= -1,SSC_INPUT_IO_TYPE,SSC_OUTPUT_IO_TYPE,NUM_IO_TYPES}
SscIoType;struct SscIoInfoTag{char const*name;SscArraySize size;char const*
unit;char const*identifier;};PMF_DEPLOY_STATIC size_t ssc_get_num_io_signals(
const SscIoInfo*ioInfoPtr,size_t ioInfoSize){size_t i=0;size_t numSignals=0;
for(i=0;i<ioInfoSize;i++){numSignals+=ssc_array_size_num_elements(&ioInfoPtr[i
].size);}return numSignals;}
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "pm_std.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct NeParameterBundleTag{PmIntVector mLogicalParameters;PmIntVector
mIntegerParameters;PmIntVector mIndexParameters;PmRealVector mRealParameters;}
NeParameterBundle;typedef struct NeDerivedParameterBundleTag{PmIntVector
mLogicalDerivedParameters;PmIntVector mIntegerDerivedParameters;PmIntVector
mIndexDerivedParameters;PmRealVector mRealDerivedParameters;}
NeDerivedParameterBundle;typedef struct NeParameterVectorTag{size_t mN;
NeParameterData*mX;}NeParameterVector;typedef struct NeParameterInfoTag{
NeParameterVector mLogicals;NeParameterVector mIntegers;NeParameterVector
mIndices;NeParameterVector mReals;}NeParameterInfo;typedef enum
SscDiagnosticSettingTag{SSC_DIAGNOSTIC_INVALID= -1,SSC_DIAGNOSTIC_ERROR,
SSC_DIAGNOSTIC_WARNING,SSC_DIAGNOSTIC_NONE,SSC_DIAGNOSTIC_NUM}
SscDiagnosticSetting;typedef enum SscLoggingSettingTag{SSC_LOGGING_INVALID= -1
,SSC_LOGGING_OFF,SSC_LOGGING_ON,SSC_LOGGING_LOCAL,SSC_LOGGING_INST,
SSC_LOGGING_NUM}SscLoggingSetting;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "pm_std.h"
#include "ne_std_fwd.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef enum NeSolverTypeTag{NE_SOLVER_TYPE_INVALID= -1,NE_SOLVER_TYPE_DAE,
NE_SOLVER_TYPE_ODE,NE_SOLVER_TYPE_DISCRETE,NE_SOLVER_TYPE_NUM}NeSolverType;
typedef enum NeModifyAbsTolTag{NE_MODIFY_ABS_TOL_INVALID= -1,
NE_MODIFY_ABS_TOL_NO,NE_MODIFY_ABS_TOL_YES,NE_MODIFY_ABS_TOL_MAYBE,
NE_MODIFY_ABS_TOL_NUM}NeModifyAbsTol;struct NeModelParametersTag{NeSolverType
mSolverType;real_T mSolverTolerance;real_T mSolverAbsTol;real_T mSolverRelTol;
boolean_T mVariableStepSolver;boolean_T mIsUsingODEN;NeModifyAbsTol
mSolverModifyAbsTol;real_T mFixedStepSize;real_T mStartTime;boolean_T
mLoadInitialState;boolean_T mUseSimState;boolean_T mLinTrimCompile;
SscLoggingSetting mLoggingMode;real_T mRTWModifiedTimeStamp;boolean_T
mZcDisabled;boolean_T mUseModelRefSolver;boolean_T mTargetFPGAHIL;};
#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "pm_std.h"
#include "ne_std_fwd.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef enum NeLocalSolverChoiceTag{NE_INVALID_ADVANCER_CHOICE= -1,
NE_BACKWARD_EULER_ADVANCER,NE_TRAPEZOIDAL_ADVANCER,NE_NDF2_ADVANCER,
NE_VARIABLE_STEP_ADVANCER,NE_PARTITIONING_ADVANCER,NE_NUM_ADVANCER_CHOICES}
NeLocalSolverChoice;typedef enum NeIndexReductionMethodTag{
NE_INVALID_IR_METHOD= -1,NE_NONE_IR,NE_DERIVATIVE_REPLACEMENT_IR,
NE_PROJECTION_IR,NE_NUM_IR_METHOD}NeIndexReductionMethod;typedef enum
NeLinearAlgebraChoiceTag{NE_INVALID_LA_CHOICE= -1,NE_AUTO_LA,NE_SPARSE_LA,
NE_FULL_LA,NE_NUM_LA_CHOICES}NeLinearAlgebraChoice;typedef enum
NeEquationFormulationChoiceTag{NE_INVALID_EF_CHOICE= -1,NE_TIME_EF,
NE_FREQUENCY_TIME_EF,NE_NUM_EF_CHOICES}NeEquationFormulationChoice;typedef enum
NePartitionStorageMethodTag{NE_PARTITIONING_INVALID= -1,
NE_PARTITIONING_AS_NEEDED,NE_PARTITIONING_EXHAUSTIVE,NE_PARTITIONING_NUM}
NePartitionStorageMethod;typedef enum NePartitionMethodTag{
NE_PARTITIONING_METHOD_INVALID= -1,NE_PARTITIONING_METHOD_ROBUST,
NE_PARTITIONING_METHOD_FAST,NE_PARTITIONING_METHOD_ALG_EQS,
NE_PARTITIONING_METHOD_ALL_EQS,NE_PARTITIONING_METHOD_MERGE,
NE_PARTITIONING_METHOD_MULTICORE,NE_PARTITIONING_METHOD_NUM}NePartitionMethod;
typedef enum NeConsistencySolverTag{NE_CONSISTENCY_SOLVER_INVALID= -1,
NE_CS_NEWTON_FTOL,NE_CS_NEWTON_XTOL,NE_CS_NEWTON_XTOL_AFTER_FTOL,
NE_CONSISTENCY_SOLVER_NUM}NeConsistencySolver;typedef enum NeToleranceSourceTag
{NE_TOLERANCE_SOURCE_INVALID= -1,NE_TOLERANCE_SOURCE_LOCAL,
NE_TOLERANCE_SOURCE_GLOBAL,NE_TOLERANCE_SOURCE_NUM}NeToleranceSource;typedef
enum NeMultibodyLocalSolverChoiceTag{NE_MULTIBODY_LOCAL_SOLVER_INVALID= -1,
NE_MULTIBODY_LOCAL_SOLVER_ODE1,NE_MULTIBODY_LOCAL_SOLVER_ODE2,
NE_MULTIBODY_LOCAL_SOLVER_ODE3,NE_MULTIBODY_LOCAL_SOLVER_ODE4,
NE_MULTIBODY_LOCAL_SOLVER_ODE5,NE_MULTIBODY_LOCAL_SOLVER_ODE8,
NE_MULTIBODY_LOCAL_SOLVER_NUM}NeMultibodyLocalSolverChoice;struct
NeSolverParametersTag{boolean_T mUseExpandedRuntimeScaling;boolean_T
mAllowRtpsInLinearSolver;boolean_T mEnableDiffOffset;boolean_T
mUseMatlabAlgebraicSolver;boolean_T mProfile;boolean_T mUseLocalSampling;
boolean_T mEnableSwitchedLinearOptims;boolean_T mFrequencyDomain;boolean_T
mUseCCode;real_T mRelTol;real_T mAbsTol;real_T mMinStep;boolean_T mToWorkspace
;boolean_T mRevertToSquareIcSolve;size_t mNumHomotopyIterations;boolean_T
mPhasorMode;size_t mPhasorModeNumHarmonics;NeConsistencySolver
mConsistencySolver;NeIndexReductionMethod mIndexReductionMethod;boolean_T mDoDC
;real_T mResidualTolerance;NeToleranceSource mConsistencyTolSource;real_T
mConsistencyAbsTol;real_T mConsistencyRelTol;real_T mConsistencyTolFactor;
boolean_T mUseLocalSolver;NeLocalSolverChoice mLocalSolverChoice;boolean_T
mResolveIndetEquations;size_t mFunctionEvalNumThread;real_T
mLocalSolverSampleTime;boolean_T mDoFixedCost;size_t mMaxNonlinIter;size_t
mMaxModeIter;boolean_T mComputeImpulses;size_t mImpulseIterations;
NeLinearAlgebraChoice mLinearAlgebra;size_t mLinearAlgebraNumThread;
NeEquationFormulationChoice mEquationFormulation;size_t mDelaysMemoryBudget;
boolean_T mAutomaticFiltering;real_T mFilteringTimeConstant;
NePartitionStorageMethod mPartitionStorageMethod;size_t mPartitionMemoryBudget
;NePartitionMethod mPartitionMethod;boolean_T mMultibodyUseLocalSolver;
NeMultibodyLocalSolverChoice mMultibodyLocalSolverChoice;real_T
mMultibodyLocalSolverSampleTime;};
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ne_std_h__ */
