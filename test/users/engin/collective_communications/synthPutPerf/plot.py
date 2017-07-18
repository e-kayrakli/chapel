import numpy as np
import matplotlib.pyplot as plt
import subprocess

numtypes = 10
strides = ('01', '02', '04', '08', '16', '32', '64')

times = [[] for i in range(numtypes)]
bars = [[] for i in range(numtypes)]

for i in range(numtypes):
    for s in strides:
        times[i].append(float(subprocess.check_output(['grep', '-R', 'Time',
            'out/type'+str(i)+'.str'+s+'.out']).split()[2]))

max_time = -1
for t in times:
    if max(t) > max_time:
        max_time = max(t)


ind = np.arange(len(strides))  # the x locations for the groups
sidemargin=0.1
width = 0.08       # the width of the bars

# plt.setsize((10,10))
fig = plt.figure(figsize=(20,10))
ax = fig.add_axes((0.1,0.1,0.8,0.8))
# fig, ax = plt.subplots()

colors=['b', 'g', 'r', 'c', 'm', 'y', '#23cdef', '#f36cba', '#adfecd',
        '#ffde98']

scaleupfactor = 1000

for t in range(numtypes):
    print(times[t])
    bars[i] = ax.bar(sidemargin+ind+width*t,
            [scaleupfactor*tt for tt in times[t]], width,
            color=colors[t], label=str(t))

# rects1 = ax.bar(ind, men_means, width, color='r')

# women_means = (25, 32, 34, 20, 25)
# women_std = (3, 5, 2, 3, 3)
# rects2 = ax.bar(ind + width, women_means, width, color='y')

# # add some text for labels, title and axes ticks
ax.set_ylabel('Access Latency(s)')
ax.set_xlabel('Stride Length')


# ax.set_title('Scores by group and gender')
ax.set_xticks(ind + 0.5)
ax.set_xticklabels([int(s) for s in strides])

# ax.set_ylim((0,scaleupfactor*max_time*1.1))
ax.set_yscale('log')

# ax.legend(handles=bars)
# ax.legend(tuple([b[0] for b in bars]), ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9'), ncol=10)
# ax.legend((rects1[0], rects2[0]), ('Men', 'Women'))
ax.legend(loc=9, ncol=10, fontsize=12)

plt.show()
