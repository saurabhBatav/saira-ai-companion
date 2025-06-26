import express from 'express';
import { getHealthStatus } from '../controllers/health.controller';

const router = express.Router();

router.get('/health', getHealthStatus);

export default router;
