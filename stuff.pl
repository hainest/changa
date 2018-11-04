use strict;
use warnings;

# This finds all globally-accessible and constant macros, but does not
# include translation unit-scope macros (e.g., #define FOO 3)
my %macros;
for my $f (glob("*.c *.cpp *.h *.ci")) {
	open my $fdIn, '<', $f or die "$f: $!\n";
	while(<$fdIn>) {
		next unless /^\s*\#/;
		next if /\#\s*include/;		# Skip non-macro lines
		next if $f=~/\.h$/ && (/\#define\s+.+_H/ || /\#ifndef\s+.+_H/);	# Skip header guards
		next if /^\s*#\s*define/;	# Skip TU macros
		next if /^\s*#\s*(warning|error)/;	# Skip warnings and errors
		next if /^\s*#\s*endif\s*/;
		next if /^\s*#\s*undef/;
		next if /^\s*#\s*else\s*/;
		chomp;
		s/\/\*.*\*\///g;
		s/^\s+//;  # strip left spaces
		s/\s+$//g; # strip right spaces
		s/\s+/ /g; # fold remaining spaces
		$macros{$_}++;
	}
}

for my $k (sort keys %macros) {
	print "$k --> $macros{$k}\n";
}

__DATA__

# Charm++ stuff
CMK_BALANCED_INJECTION_API
CMK_CHARMDEBUG
CMK_ERROR_CHECKING
CMK_HAS_INT16
CMK_LBDB_ON
CMK_LB_USER_DATA
CMK_SMP
CMK_SSE
CMK_TRACE_ENABLED
CMK_USE_AVX
CMK_USE_SSE2
CMK_VERSION_BLUEGENE
CMK_WITH_STATS

# Automatic from config
HAVE_INT64_T
HAVE_MALLOC_H
HAVE_QUAD_T
HAVE_U_INT64_T
HAVE_U_QUAD_T
HAVE_VALUES_H

# User-controlled by configure
BIGKEYS
CHANGESOFT
CUDA
COOLING_NONE
COOLING_PLANET
COOLING_COSMO
COOLING_GRACKLE
COSMO_FLOAT
CUDA_TRACE
CULLENALPHA
DAMPING
DIFFUSION
DIFFUSIONHARMONIC
DTADJUST
FEEDBACKDIFFLIMIT
HEXADECAPOLE
M4KERNEL
M6KERNEL
MERGE_REMOTE_REQUESTS
RTFORCE
SPCUDA
SPLIT_PHASE_TREE_BUILD
VSIGVISC
WENDLAND

# Not controllable by configure (but should be?)
COOLING_BATE
COOLING_DISK
COOLING_METAL
DIFFUSIONPRICE
NODIFFUSIONTHERMAL (will abort run if dThermalDiffusionCoeff is enabled in param file)
SELECTIVE_TRACING
VARALPHA (comments say it's in config, but it's not)

# Permanently turned on in Makefile (why are they macros?)
REDUCTION_HELPER

# Currently available to manually use in the Makefiles
CHANGA_REFACTOR_INTERLIST_PRINT_LIST_STATE
CHANGA_REFACTOR_MEMCHECK
CHANGA_REFACTOR_PRINT_INTERACTIONS
CHANGA_REFACTOR_WALKCHECK
CHANGA_REFACTOR_WALKCHECK_INTERLIST
CHECK_WALK_COMPLETIONS
COSMO_DEBUG
COSMO_PRINT
COSMO_STATS
CUDA_DM_PRINT_TREES
CUDA_INSTRUMENT_WRS
CUDA_PRINT_ERRORS
CUDA_PRINT_TRANSFER_BACK_PARTICLES
CUDA_PRINT_TRANSFERRED_INTERACTIONS
CUDA_STATS
CUDA_UNIT_TEST
PRINT_MERGED_TREE

# Currently manual, but should be set by configure
CUDA_2D_TB_KERNEL
CUDA_USE_CUDAMALLOCHOST
CUDA_MEMPOOL
GRACKLE_PRIMORDIAL_CHEMISTRY_MAX (defaults to 1)

# Not available in the Makefiles, but should be
CHANGA_PRINT_MEMUSAGE (roll into COSMO_DEBUG)
CONFIG_BFLOAT_4
CONFIG_BFLOAT_8 (these are required for Grackle)

# Can probably go away
ASSERTENEG
BENCHMARK_NO_WORK
CRAY_T3D
CACHE_BUFFER_MSGS
CD_SFULL
COOLDEBUG
COSMO_EVENT (typo, should be COSMO_EVENTS)
CUDAMoments_h
CUDA_NO_ACC_UPDATES
DEBUGTRACK
GP_DEBUG_EXTRAS
NEED_DT (replace with DTADJUST)
NOCOOLING (never defined- maybe it should be COOLING_NONE?)
PRINT_LOAD_PERCENTILES (only works for Orb3dLBC, but might be generally useful)
QUAD (controls long double in moments, but can't be set by user)
SINKDBG
SINKEXTRADATA
VOXEL (enabling hits an 'assert(0);')

# Should probably be in param file
EPSACCH
JEANSSOFT
JEANSSOFTONLY

# Should be converted to unit test
IMF_TST
SNIA_TST
TESTCHEMEQ
TEST_COOLING

#--------------------------------
BENCHMARK_TIME_COMPUTE
BENCHMARK_TIME_WALK
CACHE_MEM_STATS
CHANGA_REFACTOR_DEBUG
CHANGA_REFACTOR_INTERLIST_PRINT_BUCKET_START_FIN
CHECK_TIME_WITHIN_BIGSTEP
COSMO_EVENTS
DBL_MAX
DEFAULT_ARRAY_MAP
DISABLE_NODE_TREE
DO_REFINE
HPM_COUNTER
MCLBMS
MCLBMSV
NOCOMPTON
PRINT_BOUNDING_BOXES
PUSH_GRAVITY
ROUND_ROBIN_WITH_OCT_DECOMP
SINKING
SINKINGAVERAGE
STARSINK
TREE_BREADTH_FIRST
USE_PNG
VOLUMEFEEDBACK
