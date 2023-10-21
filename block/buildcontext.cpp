#include "buildcontext.h"

void BuildContext::setupGraph(const GraphTemplateBlock *block) {
  if (graphSetupDone)
    throw BuildContextException("A graph was already created.");
  graphTransform = QRect(padding, currHeight, width - padding * 2,
                         height - currHeight - padding);
  currHeight = height;
  graphSetupDone = true;
  graphBlock = block;
}

int BuildContext::axisIncrement(int min, int max) {
  int diff = max - min;
  int increment = 1;
  int m = 0;
  while (diff / increment > 10) {
    if (m == 1)
      increment = increment * 5 / 2;
    else
      increment *= 2;
    m = (m + 1) % 3;
  }
  return increment;
}
