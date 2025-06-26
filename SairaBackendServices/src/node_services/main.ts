import express from 'express';
import dotenv from 'dotenv';
import healthRoutes from './routes/health.route';
import { errorHandler } from './middleware/error.middleware';
import logger from './utils/logger';

dotenv.config();

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());
app.use('/api/v1', healthRoutes);
app.use(errorHandler);

app.listen(PORT, () => {
  console.log(`🚀 Saira backend is running on http://localhost:${PORT}`);
});
